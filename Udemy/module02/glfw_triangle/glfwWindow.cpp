#include "glfwWindow.h"
#include <iostream>


glfwWindow::glfwWindow() : mainWindow(nullptr), width(800), height(600) { }
glfwWindow::glfwWindow(GLint w, GLint h) : mainWindow(nullptr), width(w), height(h) {}
glfwWindow::~glfwWindow()
{
  glfwDestroyWindow(mainWindow);
  glfwTerminate();
}

int glfwWindow::initialise()
{
  int ret = 0;

  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // set openGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set openGL profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // set forware compatability

    mainWindow = glfwCreateWindow(width, height, "module 2 - test", nullptr, nullptr);
    if (nullptr != mainWindow)
    {
      glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

      glfwMakeContextCurrent(mainWindow);          // make the current context active
      glewExperimental = GL_TRUE;                  // allow glew experimental features

      GLenum error = glewInit();
      if (GLEW_OK == error)
      {
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, bufferWidth, bufferHeight);
      }
      else
      {
        std::cerr << "failed to initialize GLEW, error: " << glewGetErrorString(error) << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        ret = 1;
      }
    }
    else
    {
      std::cerr << "[-] failed to create GLFW window" << std::endl;
      glfwTerminate();
      ret = 1;
    }
  }
  else
  {
    std::cerr << "[-] failed to initialise GLFW" << std::endl;
    ret = 1;
  }

  return ret;
}
