#include "videosource.h"

VideoSource::VideoSource(QObject * parent) : QObject(parent)
{
}

void VideoSource::setFrame(const VideoFramePtr & frame)
{
    Q_EMIT frameReady(frame);
}
