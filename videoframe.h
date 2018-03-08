#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <QObject>
#include <QSharedPointer>
#include "surface.h"

class VideoFrame: public QObject
{
    Q_OBJECT
public:
    VideoFrame(QObject * parent = nullptr);
    VideoFrame(const QByteArray & data, const int & width, const int & height, QObject * parent = nullptr);
    ~VideoFrame();

    bool map(GLuint name);
    void unmap(GLuint name);

    int width();
    int height();

private:
    QScopedPointer<Surface> m_surface;
    void registerMetaType();
};

typedef QSharedPointer<VideoFrame> VideoFramePtr;
Q_DECLARE_METATYPE(VideoFramePtr)

#endif // VIDEOFRAME_H
