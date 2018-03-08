#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include "videoframe.h"

class VideoSource: public QObject
{
    Q_OBJECT
public:
    VideoSource(QObject * parent = nullptr);

public Q_SLOTS:
    void setFrame(const VideoFramePtr & frame);

Q_SIGNALS:
    void frameReady(const VideoFramePtr & frame);

};

#endif // VIDEOSOURCE_H
