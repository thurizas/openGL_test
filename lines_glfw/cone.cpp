#include "cone.h"

#include <stdio.h>
#include <stdlib.h>

// defines a unit right cone
cone::cone() : glObject(), m_cntSlices(5), m_cntSegments(10), m_height(1.0f), m_baseRadius(1 / sqrt3)
{
  //shader      theShader;
  calcVertices();

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertice) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// defines an arbitrary right cone
cone::cone(uint32_t sl, uint32_t sg, float h, float r) : m_cntSlices(sl), m_cntSegments(sg), m_height(h), m_baseRadius(r)
{
  calcVertices();
}

cone::~cone()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteProgram(m_shader);
}

int cone::draw()
{

  return 1;
}

void cone::calcVertices()
{
  float deltaH = m_height / m_cntSlices;
  float deltaA = 360.0f / m_cntSegments;

  for (uint32_t ndx = 0; ndx < m_cntSlices; ndx++)
  {
    float y = ndx * deltaH;                  // base sits on xz-plane
    float radius = (1-y)*m_baseRadius;

    for (float angle = 0; angle < 360; angle += deltaA)
    {
      fprintf(stderr, "theta: %6.3f, ndx: %d, radius: %6.3f ", angle, ndx, radius);
      float x = radius * cos(DEG2RAD * angle);
      float z = radius * sin(DEG2RAD * angle);
      fprintf(stderr, "(%6.3f, %6.3f, %6.3f)\n", x, y, z);
      m_vertices.push_back(vertice{ x,y,z });
    }
  }

  m_vertices.push_back(vertice{ 0.0f, m_height, 0.0f });     // apex of cone

  for(vertice v:m_vertices)
    fprintf(stderr, "(%6.3f, %6.3f, %6.3f)\n", v.x, v.y, v.z);

  // build vertex list
  // v_{i+slices}                v_{i+slices+1}
  //             *-------------*
  //             |             |
  //             |             |
  //             |             |
  //             *-------------*
  //          v_i                v_{i+1}
  fprintf(stderr, "Total number of vertices is: %I64u\n", m_vertices.size());

  for(uint32_t ndx = 0; ndx < m_cntSlices - 1; ndx++)
  {
    int sliceStart = ndx * m_cntSegments;                             // 0, 4, 8, 12  
    for (uint32_t jdx = sliceStart; jdx < sliceStart + m_cntSegments; jdx++)
    {
      int bl = jdx;
      int tl = jdx + m_cntSlices - 1;
      int br = jdx + 1;  
      if (br % (m_cntSlices - 1) == 0) br = br - m_cntSlices + 1;
      int tr = jdx + m_cntSlices;
      if (br % (m_cntSlices - 1) == 0) tr = tr - m_cntSlices + 1;

      fprintf(stderr, "[%d, %d] face: %d, %d, %d, %d\n", ndx, jdx, bl, br, tr, tl);
    }
  }

  // build faces for last slice -- these will be all triangles
  int ndx = m_cntSlices - 1;
  int sliceStart = ndx * m_cntSegments;
  int top = sliceStart + (m_cntSlices - 1);
  for (uint32_t jdx = sliceStart; jdx < sliceStart + m_cntSegments; jdx++)
  {
    int bl = jdx;
    int br = jdx + 1;
    if (br % (m_cntSlices - 1) == 0) br = br - m_cntSlices + 1;
    //int top = 
    fprintf(stderr, "[%d, %d] face: %d, %d, %d\n", ndx, jdx, bl, br, top);
  }

}