#include "videoframe.h"

VideoFrame::VideoFrame(QObject *parent): QObject(parent), m_surface(nullptr)
{
    registerMetaType();
}

VideoFrame::VideoFrame(const QByteArray & data, const int & width, const int & height, QObject * parent) : VideoFrame(parent)
{
    m_surface.reset(new Surface(data, width, height));
}

VideoFrame::~VideoFrame()
{
}

void VideoFrame::registerMetaType()
{
    static bool registered = false;
    if (!registered) {
        qRegisterMetaType<VideoFramePtr>("VideoFrame*");
        registered = true;
    }
}

bool VideoFrame::map(GLuint name)
{
    if (!m_surface) return false;
    return m_surface->map(name);
}

void VideoFrame::unmap(GLuint name)
{
    if (!m_surface) return;
    m_surface->unmap(name);
}

int VideoFrame::width()
{
    if (!m_surface) return 0;
    return m_surface->width();
}

int VideoFrame::height()
{
    if (!m_surface) return 0;
    return m_surface->height();
}
