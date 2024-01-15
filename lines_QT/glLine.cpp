#include "glLine.h"
#include "glObject.h"

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLFunctions_3_3_Core>

const char* vertSrc = "#version 330 core\n"
                      "layout(location = 0) in vec3 aPos;\n"
                      "uniform mat4 MVP;\n"
                      "void main()\n"
                      "{\n"
                      "gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                      "}\n";

const char* fragSrc = "#version 330 core\n"
                     "out vec4 FragColor;\n"
                     "uniform vec3 color;\n"
                     "void main()\n"
                     "{\n"
                     "FragColor = vec4(color, 1.0f);\n"
                     "}\n";


//line::line(QVector3D s, QVector3D e, QOpenGLFunctions_3_3_Core* pf) : glObject(), m_start(s), m_end(e), m_color(QVector3D(1, 1, 1)), m_pfncts(pf)
line::line(glm::vec3 s, glm::vec3 e, QOpenGLFunctions_3_3_Core* pf): glObject(), m_start(s), m_end(e),m_color(glm::vec3(1,1,1)), m_pfncts(pf)
{
  m_shader = new glslShader(m_pfncts);
  //m_shader->createFromFiles("./Shaders/lineVertex.glsl", "./Shaders/lineFragment.glsl");
  m_shader->createFromStrings(vertSrc, fragSrc);

  //vertices = { m_start.x(), m_start.y(), m_start.z(),m_end.x(), m_end.y(), m_end.z(), };
  vertices = { m_start.x, m_start.y, m_start.z, m_end.x, m_end.y, m_end.z };

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
  //m_pfncts->glUniformMatrix4fv(m_pfncts->glGetUniformLocation(m_shader->getProgramID(), "MVP"), 1, GL_FALSE, MVP.data());
  m_pfncts->glUniformMatrix4fv(m_pfncts->glGetUniformLocation(m_shader->getProgramID(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

  m_pfncts->glBindVertexArray(m_vao);
  m_pfncts->glDrawArrays(GL_LINES, 0, 2);


  return 1;
}

//void line::setColor(QVector3D c)
void line::setColor(glm::vec3 c)
{
  m_color = c;
}

//void line::setMVP(QMatrix4x4 m)
void line::setMVP(glm::mat4 m)
{
  MVP = m;
}
