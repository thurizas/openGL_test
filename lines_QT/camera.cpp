#include "camera.h"
#include "constants.h"

#include <iostream>

//#include <QMatrix4x4>
//#include <QVector3D>

#include <QOpenGlFunctions_3_3_core>

camera::camera() : m_pos(glm::vec3(0, 0, 0))
{ }

camera::~camera() {}