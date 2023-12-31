#ifndef _cone_h_
#define _cone_h_

#include <cstdint>

#include "glObject.h"
#include "shader.h"

#include <vector>

static const float pi = 3.1415926536f;
static const float sqrt2 = 1.4142135624f;
static const float sqrt3 = 1.7320508076f;
static const float DEG2RAD = pi / 180.0f;

typedef struct _v
{
  float   x;
  float   y;
  float   z;
} vertice, *pvertice;

class cone : public glObject
{
public:
  cone();
  cone(uint32_t, uint32_t, float, float);
  ~cone();

  int draw();

private:
  uint32_t             m_cntSlices;
  uint32_t             m_cntSegments;
  float                m_height;
  float                m_baseRadius;
  std::vector<vertice> m_vertices;
  std::vector<int>     m_indices;

  void calcVertices();
};




#endif
