#ifndef _camera_h_
#define _camera_h_

//#include <QMatrix4x4>
//#include <QVector3D>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <QOpenGlFunctions_3_3_core>

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