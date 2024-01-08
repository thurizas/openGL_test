#include "glLine.h"
#include "glObject.h"

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLFunctions_3_3_Core>


line::line(QVector3D s, QVector3D e, QOpenGLFunctions_3_3_Core* pf) : glObject(), m_start(s), m_end(e), m_color(QVector3D(1, 1, 1)), m_pfncts(pf)
{
  m_shader = new glslShader(m_pfncts);
  m_shader->createFromFiles("./Shaders/lineVertex.glsl", "./Shaders/lineFragment.glsl");

  vertices = { m_start.x(), m_start.y(), m_start.z(),m_end.x(), m_end.y(), m_end.z(), };

  m_pfncts->glGenVertexArrays(1, &m_vao);
  m_pfncts->glGenBuffers(1, &m_vbo);
  m_pfncts->glBindVertexArray(m_vao);

  m_pfncts->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  m_pfncts->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  m_pfncts->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  m_pfncts->glEnableVertexAttribArray(0);

  m_pfncts->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_pfncts->glBindVertexArray(0);

}

line::~line()
{
  m_pfncts->glDeleteVertexArrays(1, &m_vao);
  m_pfncts->glDeleteBuffers(1, &m_vbo);
  m_pfncts->glDeleteProgram(shaderProgram);

  if (nullptr != m_shader) delete m_shader;
}


int line::draw()
{
  m_shader->useShader();

  m_pfncts->glUniform3fv(m_pfncts->glGetUniformLocation(m_shader->getProgramID(), "color"), 1, &m_color[0]);
  m_pfncts->glUniformMatrix4fv(m_pfncts->glGetUniformLocation(m_shader->getProgramID(), "MVP"), 1, GL_FALSE, MVP.data());

  m_pfncts->glBindVertexArray(m_vao);
  m_pfncts->glDrawArrays(GL_LINES, 0, 2);
  return 1;
}

void line::setColor(QVector3D c)
{
  m_color = c;
}

void line::setMVP(QMatrix4x4 m)
{
  MVP = m;
}
