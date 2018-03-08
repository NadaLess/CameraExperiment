#ifndef CAMERAFRAMEGRABBER_H
#define CAMERAFRAMEGRABBER_H

// Qt includes
#include <QAbstractVideoSurface>
#include <QList>

class CameraFrameGrabber : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraFrameGrabber(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool present(const QVideoFrame &frame);

signals:
    void frameAvailable(const QVideoFrame &frame);
};

#endif // CAMERAFRAMEGRABBER_H
