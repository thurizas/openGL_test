#ifndef _glshaders_h_
#define _glshaders_h_

#include <string>
#include <iostream>
#include <fstream>

#include <QOpenGLFunctions_3_3_Core>

class glslShader
{
public:
  glslShader(QOpenGLFunctions_3_3_Core* pfncts);
  ~glslShader();

  GLuint getProgramID() { return m_shaderID; }
  void   useShader();

  void createFromStrings(const char* vCode, const char* fCode, const char* gCode = nullptr);
  void createFromFiles(const char* vFile, const char* fFile, const char* gFile = nullptr);


private:
  std::string    readFile(const char* fileName);
  void           compileShader(const char* vCode, const char* fCode, const char* gCode = nullptr);
  void           addShader(GLuint, const char*, GLenum);

  void           clearShader();

  QOpenGLFunctions_3_3_Core* m_fncts;

  GLuint          m_shaderID = 0;
  GLuint          m_uProjection = 0;          // uniform to hold projection matrix
  GLuint          m_uModel = 0;               // uniform to hold model matrix
  GLuint          m_uView = 0;                // uniform to hold view matrix
};

#endif
