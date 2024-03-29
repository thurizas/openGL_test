#ifndef _globject_h_
#define _globject_h_

#include <cstdint>

//#include <QMatrix4x4>
#include <glm/glm.hpp>

typedef struct _v
{
  float   x;
  float   y;
  float   z;
} vertex, * pvertex;

class glObject
{
public:
  glObject();
  ~glObject();

  static int getCnt() { return m_cnt++; }

  virtual int draw() = 0;
  //virtual void setMVP(QMatrix4x4) = 0;
  virtual void setMVP(glm::mat4) = 0;

protected:
  int m_shader;
  unsigned int m_vao, m_vbo;
  uint32_t   m_id;

private:
  static int m_cnt;

};

#endif
