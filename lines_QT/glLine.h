#ifndef _line_h_
#define _line_h_

#include <vector>

//#include <QVector3D>
//#include <QMatrix4x4>

#include <QOpenGLFunctions_3_3_Core>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "glObject.h"
#include "GLShaders.h"

class line : public glObject
{
public:
  line();
  //line(QVector3D, QVector3D, QOpenGLFunctions_3_3_Core*);
  line(glm::vec3, glm::vec3, QOpenGLFunctions_3_3_Core*);
  ~line();

  //void setMVP(QMatrix4x4 m);
  //QMatrix4x4 getMVP();
  void setMVP(glm::mat4 m);
  glm::mat4 getMVP();

  //void setColor(QVector3D c);
  //QVector3D getColor();
  void setColor(glm::vec3 c);
  glm::vec3 getColor();

  int draw();

private:
  QOpenGLFunctions_3_3_Core*      m_pfncts;
  //glslShaders theShader;
  glslShader*                     m_shader;
  glm::vec3/*QVector3D*/          m_start;
  glm::vec3/*QVector3D*/          m_end;
  glm::vec3/*QVector3D*/          m_color;

  int shaderProgram;
  unsigned int m_vao, m_vbo;

  std::vector<float> vertices;

  glm::mat4/*QMatrix4x4*/ MVP=glm::mat4(1.0);

};

#endif