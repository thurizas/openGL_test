#ifndef _util_h_
#define _util_h_


#include <GL/glew.h>
#include <iostream>


#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef _DEBUG

static void GLClearError() { while (glGetError() != GL_NO_ERROR); }            // clear the error buffer

static bool GLLogCall(const char* fun, const char* file, int line)              // get the error(s) from the function call
{
  while (GLenum error = glGetError())
  {
    std::cout << "[OpenGL error] (" << error << "): " << fun << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))                            // macro to wrap OpenGL calls
#else
#define GLCall(x) x
#endif

// functions to load shader programs from file
std::string shaderFromFile(const char* name);
bool shaderFromFile(const char* name, char** source);

// functions to check and report errors in compiling and linking programs
bool checkShader(GLuint shader);
bool checkLink(GLuint program);
static void printShaderLog(GLuint shader);
static void printProgramLog(GLuint prog);


#endif 