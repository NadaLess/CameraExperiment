#include "cameraexperiment.h"
#include "libyuv.h"
#include <QByteArray>
#include <QDebug>

CameraExperiment::CameraExperiment(QObject *parent) : VideoSource(parent)
{
    m_camera = new QCamera(this);
    m_frameGrabber = new CameraFrameGrabber(this);
    m_camera->setViewfinder(m_frameGrabber);


    QCameraViewfinderSettings settings;
    settings.setResolution(1280, 720);

    m_camera->setViewfinderSettings(settings);

    connect(m_frameGrabber, &CameraFrameGrabber::frameAvailable, this, &CameraExperiment::handleFrame);
    m_camera->start();
}

CameraExperiment::~CameraExperiment()
{
    m_camera->stop();
}

void CameraExperiment::handleFrame(const QVideoFrame &frame)
{
    if (frame.isValid()) {
        qDebug() << "CameraFrame:" << frame;

        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

        QByteArray data;
        size_t sizeRGB24 = cloneFrame.width() * cloneFrame.height() * 3;

        QVideoFrame::PixelFormat fmt = frame.pixelFormat();
        switch(fmt) {
        case QVideoFrame::Format_RGB24:
            data = QByteArray((char*)cloneFrame.bits(), sizeRGB24);
            break;
        case QVideoFrame::Format_RGB32:
            data.resize(sizeRGB24);
            libyuv::ARGBToRGB24(cloneFrame.bits(), cloneFrame.bytesPerLine(),
                                (uint8_t*)data.data(), cloneFrame.width() * 3,
                                cloneFrame.width(), cloneFrame.height());
            break;
        default:
            qDebug() << "Conversion not supported for:" << fmt;
        }

        Q_EMIT frameReady(VideoFramePtr(new VideoFrame(data,
                                                       cloneFrame.width(),
                                                       cloneFrame.height())));
        cloneFrame.unmap();
    }
}
