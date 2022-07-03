#ifndef _common_h_
#define _common_h_

#include <QOpenGlFunctions_3_3_Core>
#include <QDebug>

#include <iostream>

// we stick this define here, as this file is include everywhere we might want to use is
#define ASSERT(x) if(!(x)) __debugbreak();


// macros for getting return errors from OpenGL calls...
#ifdef __DEBUG

static void GLClearError(QOpenGLFunctions_3_3_Core* p) { while (p->glGetError() != GL_NO_ERROR); }            // clear the error buffer

static bool GLLogCall(QOpenGLFunctions_3_3_Core* p, const char* fun, const char* file, int line)              // get the error(s) from the function call
{
  while (GLenum error = p->glGetError())
  {
    std::cout << "[OpenGL error] (" << error << "): " << fun << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

#define GLCall(p, x) GLClearError(p);x;ASSERT(GLLogCall(p, #x, __FILE__, __LINE__))                            // macro to wrap OpenGL calls
#else
#define GLCall(x) x
#endif

#endif

static void normalizeAngle(int& angle)
{
  while (angle < 0) angle += 360 * 16;

  while (angle > 360 * 16) angle -= 360 * 16;
}
