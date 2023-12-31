#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

camera::camera() : m_pos(glm::vec3(0, 0, 0))
{ }

camera::~camera() {}