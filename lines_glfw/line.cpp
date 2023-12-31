#include "line.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


  line::line(glm::vec3 s, glm::vec3 e) : glObject(), m_start(s), m_end(e), m_color(glm::vec3(1,1,1)) 
  {
    theShader.CreateFromFiles("./Shaders/lineVertex.glsl", "./Shaders/lineFragment.glsl");

    vertices = {m_start.x, m_start.y, m_start.z,m_end.x, m_end.y, m_end.z,};

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

  }

line::~line()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(shaderProgram);
}


int line::draw() 
{
  theShader.UseShader();
  
  glUniform3fv(glGetUniformLocation(theShader.programID(), "color"), 1, &m_color[0]);
  glUniformMatrix4fv(glGetUniformLocation(theShader.programID(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

  glBindVertexArray(m_vao);
  glDrawArrays(GL_LINES, 0, 2);
  return 1;
}

void line::setColor(glm::vec3 c)
{
  m_color = c;
}

void line::setMVP(glm::mat4 m)
{
  MVP = m;
}


