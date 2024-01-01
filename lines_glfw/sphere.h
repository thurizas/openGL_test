#ifndef _sphere_h_
#define _sphere_h_
/*
 *  we represent the sphere by a series of slices (horizontal chunks) and segments (vertical chunks)
 *  roughly correlated with latitude and longitude.  If we "skin" the sphere and roll out
 *  the resulting grid we get: (each pole is represented by a single point)
 *  We are assuming that we have 6 slices and 4 segments.
 * 
 *             0          90        180        270        360
 *      90 N   +---------------------*---------------------+
 *             |          |          |0         |          |
 *             |          |          |          |          |
 *             |          |          |          |          |
 *      60 N   *----------*----------*----------*----------*
 *             |1         |2         |3         |4         |1
 *             |   f6     |          |          |          |
 *             |          |          |          |          |
 *      30 N   *----------*----------*----------*----------*
 *             |5         |6         |7         |8         |5
 *             |          |          |          |          |
 *             |          |          |          |          |
 *        0    *----------*----------*----------*----------*
 *             |9         |10        |11        |12        |9
 *             |          |          |          |          |
 *             |          |          |          |          |
 *       30 S  *----------*----------*----------*----------*
 *             |13        |14        |15        |16        |13
 *             |          |          |          |          |
 *             |          |          |          |          |
 *       60 s  *----------*----------*----------*----------*
 *             |17        |18        |19        |20        |17
 *             |          |          |          |          |
 *             |          |          |          |          |
 *       90 s  +---------------------*---------------------+
 *                                    21           
 * 
 *  where '*' represent calculated vertices and number represent where in the array of 
 *  vertices the vertex is located.  faces 1 through 6 are trangular faces build from the
 *  penultimate slice and the last slice (i.e. face f1 is composed on vertices 0, 2,1);
 *  while f6 is comprised of vertices 7, 8,2,1.
 *     In wire-frame mode we need a number of line-strips, instead of a collection of 
 *  triangular faces.
 * 
 * To keep calculations simpler, we assume that this models a unit sphere, centered at the
 * origin.  theta = azimuthal angle, measured clockwise from positive x axis range is [0, 360) 
 *          phi = polar angle, measured done from positive z axis, range is [90, -90]
 *           x  = rcos(theta)sin(phi)
 *           y  = rsin(theta)sin(phi)
 *           z  = rcos(phi)
 */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>

#include "glObject.h"
#include "shader.h"

#include <vector>

class sphere : public glObject
{
public:
  sphere();
  sphere(uint32_t, uint32_t, bool wf = false);
  ~sphere();

  void color(glm::vec3 c) { m_color = c; }
  glm::vec3 color() { return m_color; }

  void mvp(glm::mat4 t) { m_mvp = t; }
  glm::mat4 mvp() { return m_mvp; }

  int draw();

private:
  Shader               theShader;
  GLuint               m_ibo;
  uint32_t             m_cntSlices;
  uint32_t             m_cntSegments;
  bool                 m_wireFrame;
  std::vector<vertex>  m_vertices;
  std::vector<int>     m_indices;

  void                 calcVertices();
  void                 genSolidBuffers();
  void                 genWFBuffers();

  // uniforms
  glm::vec3            m_color;
  glm::mat4            m_mvp = glm::mat4(1.0);

};

#endif
