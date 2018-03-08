#ifndef CAMERAEXPERIMENT_H
#define CAMERAEXPERIMENT_H

#include <QQmlEngine>
#include "videosource.h"
#include <QCamera>
#include "cameraframegrabber.h"

class CameraExperiment : public VideoSource
{
    Q_OBJECT
public:
    explicit CameraExperiment(QObject *parent = nullptr);
    ~CameraExperiment();

private Q_SLOTS:
    void handleFrame(const QVideoFrame & frame);

private:
    QCamera * m_camera;
    CameraFrameGrabber * m_frameGrabber;
};


// Qml Singleton callback
static QObject *cameraInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new CameraExperiment;
}
#endif // CAMERAEXPERIMENT_H
