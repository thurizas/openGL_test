#ifndef _line_h_
#define _line_h_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glObject.h"
#include "shader.h"

class line : public glObject
{
public:
  line();
  line(glm::vec3, glm::vec3);
  ~line();

  void setMVP(glm::mat4 m);
  glm::mat4 getMVP();

  void setColor(glm::vec3 c);
  glm::vec3 getColor();

  int draw();

private:
  Shader    theShader;
  glm::vec3 m_start;
  glm::vec3 m_end;
  glm::vec3 m_color;

  int shaderProgram;
  unsigned int m_vao, m_vbo;

  std::vector<float> vertices;

  glm::mat4 MVP = glm::mat4(1.0);
};

#endif