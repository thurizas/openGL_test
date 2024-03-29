#ifndef _cone_h_
#define _cone_h_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>

#include "glObject.h"
#include "shader.h"
#include "constants.h"

#include <vector>



//typedef struct _v
//{
//  float   x;
//  float   y;
//  float   z;
//} vertice, *pvertice;

class cone : public glObject
{
public:
  cone();
  cone(uint32_t, uint32_t, float, float);
  ~cone();

  glm::vec3 color() { return m_color; }
  void color(glm::vec3 c) { m_color = c; }

  glm::mat4 mvp() { return m_MVP; }
  void mvp(glm::mat4 m) { m_MVP = m; }

  int draw();

private:
  Shader               theShader;
  GLuint               m_ibo;
  uint32_t             m_cntSlices;
  uint32_t             m_cntSegments;
  float                m_height;
  float                m_baseRadius;
  std::vector<vertex> m_vertices;
  std::vector<int>     m_indices;

  // uniforms
  glm::vec3            m_color;
  glm::mat4            m_MVP = glm::mat4(1.0);


  void calcVertices();
};




#endif
