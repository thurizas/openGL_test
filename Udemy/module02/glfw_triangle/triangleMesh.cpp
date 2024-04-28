#include <cstdint>

#include "triangleMesh.h"

triangleMesh::triangleMesh() : VAO(0), VBO(0), IBO(0), cntNdx(0) { }
triangleMesh::~triangleMesh() { clearMesh(); }

void triangleMesh::createMesh(GLfloat* vertices, uint32_t* indices, uint32_t cntVertices, uint32_t cntIndices)
{
  cntNdx = cntIndices;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * cntIndices, indices, GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * cntVertices, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void triangleMesh::renderMesh()
{
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glDrawElements(GL_TRIANGLES, cntNdx, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


void triangleMesh::clearMesh()
{
  if (IBO != 0) { glDeleteBuffers(1, &IBO); IBO = 0; }
  if (VBO != 0) { glDeleteBuffers(1, &VBO); VBO = 0; }
  if (VAO != 0) { glDeleteBuffers(1, &VAO); VAO = 0; }

  cntNdx = 0;
}
