#ifndef _tetrahedron_h_
#define _tetrahedron_h_

#include <QVector>
#include <QColor>


class point3f
{
public:
  point3f() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_data{ 0 } {}
  point3f(float x, float y, float z) : m_x(x), m_y(y), m_z(z), m_data{ x,y,z } {}

  void x(float x) { m_x = x; m_data[0] = x; }
  float x() { return m_x; }

  void y(float y) { m_y = y; m_data[1] = y; }
  float y() { return m_y; }

  void z(float z) { m_z = z; m_data[2] = z; }
  float z() { return m_z; }

  const float* data() const { return m_data; }

  friend point3f operator-(const point3f& op1, const point3f& op2)
  {
    point3f ret = point3f((op1.m_x - op2.m_x), (op1.m_y - op2.m_y), (op1.m_z - op2.m_z));
    return ret;
  }

  // treating two points as vectors (which they are abstractly), calculate the cross-product of them
  friend point3f operator* (const point3f& op1, const point3f& op2)
  {
    float x = op1.m_y * op2.m_z - op1.m_z * op2.m_y;
    float y = op1.m_x * op2.m_z - op1.m_z * op2.m_x;
    float z = op1.m_x * op2.m_y - op1.m_y * op2.m_x;

    point3f ret = point3f(x, y, z);
    return ret;
  }

private:
    float m_x;
    float m_y;
    float m_z;
    float m_data[3];

};


class tetrahedron
{
public:
  tetrahedron();
  ~tetrahedron();

  const float* constData() const;
  const float* constNorms() const;
  const uint32_t* indicies() const;

  uint32_t cntVerticies() { return m_cntVerticies; }
  uint32_t cntIndices() { return m_cntIndicies; }

private:
  void        calcNormals();

  point3f     m_v1;
  point3f     m_v2;
  point3f     m_v3;
  point3f     m_v4;
  uint32_t    m_ndx[12];                // vertex index for the four faces
  float       m_data[12];               // vertex values for the four verticies
  uint32_t    m_cntIndicies;
  uint32_t    m_cntVerticies;           // number of verticies in the figure
  float       m_normal[12];             // outward facing normals for the four faces
  QColor      m_color;
};

#endif
