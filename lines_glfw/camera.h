#ifndef _camera_h_
#define _camera_h_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:
  camera();
  ~camera();

  void pos(glm::vec3 v) { m_pos = v; }
  glm::vec3 pos() { return m_pos; }

private:
  glm::vec3   m_pos;
};

#endif;

