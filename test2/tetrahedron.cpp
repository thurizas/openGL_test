#include "tetrahedron.h"

#include <cmath>

/************************************************************************************************************************
 * function  : ctor 
 *
 * abstract  : This function constructs a unit tetrahedron centered at the origin.  The four verticies are located at
 *             v1 = (0,0,1)  
 *             v2 = (-sqrt(2/9), -sqrt(2/3), -1/3)
 *             v3 = (sqrt(8/9), 0, -1/3)
 *             v4 = (-sqrt(2/9), sqrt(2/3), -1/3)
 * 
 *             there are four faces, the f1 is composed of v2, v4, v3 (ccw)
 *                                       f2 is composed of v1, v3, v4 (ccw)
 *                                       f3 is composed of v1, v4, v2 (ccw)
 *                                       f4 is composed of v1, v2, v3 (ccw)
 * 
 *             f_i is opposite v_i in all cases.
 *             All coordinates must be in the range [-1, 1] or they will not be drawn
 * parameters:
 *
 * returns   :
 *
 * written   : Jul 2022 (GKHuber)
************************************************************************************************************************/
tetrahedron::tetrahedron() : m_data{ 0 }, m_cntIndicies(12), m_cntVerticies(4)
{
  float   r1 = sqrt(8.0f / 9.0f);
  float   r2 = sqrt(2.0f / 9.0f);
  float   r3 = sqrt(2.0f / 3.0f);

  m_v1 = point3f(0.0f, 0.0f, 1.0f);
  m_v2 = point3f(-r2, -r3, -1.0f / 3.0f);
  m_v3 = point3f(r1, 0.0f, 1.0f / 3.0f);
  m_v4 = point3f(-r2, r3, -1.0f / 3.0f);

  m_ndx[0] = 1; m_ndx[1] = 3; m_ndx[2] = 2;        // verticies for f1
  m_ndx[3] = 0; m_ndx[4] = 2; m_ndx[5] = 3;        // verticies for f2
  m_ndx[6] = 0; m_ndx[7] = 3; m_ndx[8] = 1;        // verticies for f3
  m_ndx[9] = 0; m_ndx[10] = 1; m_ndx[11] = 2;      // verticies for f4

  calcNormals();
}

tetrahedron::~tetrahedron()
{

}


/*
r1 = 0.942809045 = 0x
r2 = 0.471404523 = 0x 
r3 = 0.816496611 = 0x
*/
const float* tetrahedron::constData() const
{
  memcpy((void*)&m_data[0], m_v1.data(), 3 * sizeof(float));
  memcpy((void*)&m_data[3], m_v2.data(), 3 * sizeof(float));
  memcpy((void*)&m_data[6], m_v3.data(), 3 * sizeof(float));
  memcpy((void*)&m_data[9], m_v4.data(), 3 * sizeof(float));

  return m_data;
}

const float* tetrahedron::constNorms() const
{
  return m_normal;
}

const uint32_t* tetrahedron::indicies() const
{
  return m_ndx;
}


/************************************************************************************************************************
 * function : calcNormals
 *
 * abstract  : This calculates the normals for a face, given that the vertices are given in counter-clockwise order by
 * 
 *             F_{i,n} = (v_{i_2} - v_{i_1})\times(v_{i_3} - v_{i_2})
 * 
 *             i.e. the cross product of two vectors lieing in the plane.  Note that the vertices are given in increasing
 *                  order sorted by the indicies: F1 : v2,v3,v4; F2:v1,v4,v3; F3: v1,v2,v4; and F4 : v1,v3,v2
 *                  (ref: https://math.stackexchange.com/questions/183030/given-a-tetrahedron-how-to-find-the-outward-surface-normals-for-each-side
 *
 * parameters:
 *
 * returns   :
 *
 * written   : Jul 2022 (GKHuber)
************************************************************************************************************************/
void tetrahedron::calcNormals()
{
  point3f f1 = (m_v3 - m_v2) * (m_v4 - m_v3);
  point3f f2 = (m_v4 - m_v1) * (m_v3 - m_v4);
  point3f f3 = (m_v2 - m_v1) * (m_v4 - m_v2);
  point3f f4 = (m_v3 - m_v1) * (m_v2 - m_v3);

  memcpy((void*)&m_normal[0], f1.data(), 3 * sizeof(float));
  memcpy((void*)&m_normal[3], f2.data(), 3 * sizeof(float));
  memcpy((void*)&m_normal[6], f3.data(), 3 * sizeof(float));
  memcpy((void*)&m_normal[9], f4.data(), 3 * sizeof(float));
}