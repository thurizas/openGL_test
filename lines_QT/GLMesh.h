#ifndef _glgrid_h_
#define _glgrid_h_

#include <cstdint>
#include <QOpenGLFunctions_3_3_Core>

class mesh
{
public:
  mesh(QOpenGLFunctions_3_3_Core*);
  virtual ~mesh();

  virtual void createMesh() = 0;
  virtual void renderMesh(QMatrix4x4) = 0;
  virtual void clearMesh() = 0;

protected:
  QOpenGLFunctions_3_3_Core* m_fncts;
  GLuint         m_vao = 0;
  GLuint         m_vbo = 0;
  GLuint         m_ibo = 0;

  GLsizei        m_cntNdx;
};


#endif