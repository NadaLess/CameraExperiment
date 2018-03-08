#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cameraexperiment.h"
#include "videorenderer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<CameraExperiment>("CameraExperiment", 1, 0, "DNCamera", cameraInstance);
    qmlRegisterType<VideoFBORenderer>("CameraExperiment", 1, 0, "VideoRenderer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
