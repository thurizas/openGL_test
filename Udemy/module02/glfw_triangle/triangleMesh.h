#ifndef _triangleMesh_h_
#define _triangleMesh_h_

#include <GL\glew.h>

class triangleMesh
{
public:
  triangleMesh();
  ~triangleMesh();

  void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t cntVertices, uint32_t cntIndices);
  void renderMesh();
  void clearMesh();

private:
  GLuint   VAO;
  GLuint   VBO;
  GLuint   IBO;

  GLsizei  cntNdx;

};

#endif
