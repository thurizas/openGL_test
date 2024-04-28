#ifndef _shader_h_
#define _shader_h_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class CShader
{
public:
  CShader();
  ~CShader();

  void createFromStrings(const char* vextex, const char* fragment);
  void createFromFiles(const char* vertex, const char* fragment);

  std::string readFile(const char* name);

  GLuint getProjectionLocation() { return uProjection; }
  GLuint getModelLocation() { return uModel; }

  void useShader();
  void clearShader();

private:
  GLuint shaderID;
  GLuint uProjection;
  GLuint uModel;

  void compileShader(const char* vertex, const char* fragmetn);
  void addShader(GLuint, const char*, GLenum);
};

#endif

