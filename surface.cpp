#include "surface.h"
#include <QDebug>

Surface::Surface(const QByteArray & data, const int & width, const int & height, QObject * parent)
    : QObject(parent),
      m_width(width),
      m_height(height)
{
    m_rgbData = data;
}

Surface::~Surface() {
    m_rgbData.clear();
}

bool Surface::map(GLuint name) {
    initGLFunctions();

    if (m_rgbData.isEmpty()) return false;

    m_glFunctions.glBindTexture(GL_TEXTURE_2D, name);
    m_glFunctions.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                  GL_UNSIGNED_BYTE, m_rgbData.data());

    return true;
}

bool Surface::unmap(GLuint name){
    Q_UNUSED(name)
    m_glFunctions.glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

int Surface::width() {
    return m_width;
}

int Surface::height() {
    return m_height;
}

void Surface::initGLFunctions()
{
    static bool glInitialized = false;
    if (!glInitialized)
        m_glFunctions.initializeOpenGLFunctions();
}
