#include "sphere.h"
#include "constants.h"



sphere::sphere() : m_ibo(0), m_cntSlices(0), m_cntSegments(0), m_wireFrame(false)
{
  theShader.CreateFromFiles("./Shaders/coneVertex.glsl", "./Shaders/coneFragment.glsl");
  calcVertices();
}

sphere::sphere(uint32_t sl, uint32_t sg, bool wf) : m_ibo(0), m_cntSlices(sl), m_cntSegments(sg), m_wireFrame(wf)
{
  theShader.CreateFromFiles("./Shaders/coneVertex.glsl", "./Shaders/coneFragment.glsl");
  calcVertices();
}

sphere::~sphere()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteProgram(m_shader);
}

int sphere::draw()
{
  theShader.UseShader();

  glUniform3fv(glGetUniformLocation(theShader.programID(), "color"), 1, &m_color[0]);
  glUniformMatrix4fv(glGetUniformLocation(theShader.programID(), "MVP"), 1, GL_FALSE, &m_mvp[0][0]);

  glBindVertexArray(m_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return 1;
}

void sphere::calcVertices()
{
  float deltaLat = 180.0f / m_cntSlices;
  float deltaLon = 360.0f / m_cntSegments;

  // (1) calculate zenith of sphere
  m_vertices.push_back(vertex{ 0.0f, 0.0f, 1.0f });

  // (2) calculate the other points 
  for (float lat = deltaLat; lat < 180.0f; lat = lat + deltaLat)
  {
    float z = cos(DEG2RAD * lat);
    float r1 = sin(DEG2RAD * lat);

    for (float lon = 0; lon < 360; lon = lon + deltaLon)
    {
      float x = cos(DEG2RAD * lon) * r1;
      float y = sin(DEG2RAD * lon) * r1;

      m_vertices.push_back(vertex{ x, y, z });
    }
  }

  // (3) calculate nader of sphere
  m_vertices.push_back(vertex{ 0.0f, 0.0f, -1.0f });


  // create the basic openGL buffer objects......
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  if (m_wireFrame) genWFBuffers();
  else genSolidBuffers();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void sphere::genSolidBuffers()
{
  int top = 0;                              // index of top most vertex
  int bottom = (int)m_vertices.size()-1;    // index of bottom most vertex
   
  // special case handle top-most slice (all triangles)
  uint32_t row = 1;
  for (uint32_t ndx = 1; ndx <= m_cntSegments; ndx++)
  {
    int bl = ndx;
    int br = ndx + 1;
    if (br % m_cntSegments == 1) br = br - m_cntSegments;
    m_indices.push_back(bl); m_indices.push_back(br); m_indices.push_back(top);
  }

  // TODO : handle 2 to n-1 slices (two triangles per quad)
  for(uint32_t row = 2; row < m_cntSlices; row++)                                               // m_cntSlices = 6   row: 2, 3, 4,  5
  {
    for (uint32_t col = (row - 1) * m_cntSegments + 1; col <= row * m_cntSegments; col++)       // m_cntSegments = 4 col: 5,  9, 13, 17                  
    {                                                                                           //                        9, 13, 17, 21                              
      int bl = col;                                             // bottom left of quadrilateral
      int tl = col - m_cntSegments;                             // top left of quadrilateral
      int br = col + 1;                                         // bottom right of quadrilateral
      if (br % m_cntSegments == 1) br = br - m_cntSegments;
      int tr = br - m_cntSegments;                              // top right of quadrilateral
      m_indices.push_back(bl); m_indices.push_back(br); m_indices.push_back(tr);
      m_indices.push_back(tr); m_indices.push_back(tl); m_indices.push_back(bl);
    }
  }

  // handle special case of bottom-most slice all triangles
  row = m_cntSlices - 2;
  for (uint32_t ndx = row * m_cntSegments + 1; ndx <= (row + 1)* m_cntSegments; ndx++)
  {
    int tl = ndx;                                         
    int tr = ndx + 1;
    if (tr % m_cntSegments == 1 ) tr = tr - m_cntSegments;
    m_indices.push_back(bottom); m_indices.push_back(tr); m_indices.push_back(tl);
  }

  glGenBuffers(1, &m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
}

void sphere::genWFBuffers()
{
  glGenBuffers(1, &m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
}