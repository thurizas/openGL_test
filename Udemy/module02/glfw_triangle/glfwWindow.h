#ifndef _glfwWindow_h_
#define _glfwWindow_h_

#include <GL\glew.h>
#include <GLFW\glfw3.h>



class glfwWindow
{
public:
  glfwWindow();
  glfwWindow(GLint windowWidth, GLint windowHeight);
  ~glfwWindow();

  int initialise();

  GLint getBufferWidth() { return bufferWidth; }
  GLint getBufferHeight() { return bufferHeight; }

  bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

  void swapBuffers() { glfwSwapBuffers(mainWindow); }

private:
  GLFWwindow* mainWindow;
  GLint       width;
  GLint       height;
  GLint       bufferWidth;
  GLint       bufferHeight;
};

#endif