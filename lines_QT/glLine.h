#ifndef _line_h_
#define _line_h_

#include <vector>

#include <QVector3D>
#include <QMatrix4x4>

#include <QOpenGLFunctions_3_3_Core>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "glObject.h"
#include "GLShaders.h"

class line : public glObject
{
public:
  line();
  line(QVector3D, QVector3D, QOpenGLFunctions_3_3_Core*);
  ~line();

  void setMVP(QMatrix4x4 m);
  QMatrix4x4 getMVP();

  void setColor(QVector3D c);
  QVector3D getColor();

  int draw();

private:
  QOpenGLFunctions_3_3_Core*      m_pfncts;
  //glslShaders theShader;
  glslShader*                     m_shader;
  QVector3D                       m_start;
  QVector3D                       m_end;
  QVector3D                       m_color;

  int shaderProgram;
  unsigned int m_vao, m_vbo;

  std::vector<float> vertices;

  QMatrix4x4 MVP;

};

#endif