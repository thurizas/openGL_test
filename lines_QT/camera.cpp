#include "camera.h"
#include "constants.h"

#include <QMatrix4x4>
#include <QVector3D>

#include <QOpenGlFunctions_3_3_core>

Camera::Camera()
{

}


Camera::Camera(QVector3D pos, QVector3D up, float yaw, float pitch, float moveSpd, float turnSpd)
{
  m_pos = pos;
  m_worldUp = up;
  m_yaw = yaw;
  m_pitch = pitch;

  m_front = QVector3D(0.0f, 0.0f, -1.0f);

  update();
  m_lookAt.setToIdentity();
}

Camera::~Camera()
{

}


QMatrix4x4 Camera::calcViewMatrix()
{
  update();
  m_lookAt.setToIdentity();

  m_lookAt.lookAt(m_pos, m_pos + m_front, m_up);

  return m_lookAt;
}

// pitch and yaw are assumed to be in degrees
void Camera::update()
{
  m_front.setX(cos(m_yaw * DEG2RAD) * cos(m_pitch * DEG2RAD));
  m_front.setY(sin(m_pitch * DEG2RAD));
  m_front.setZ(sin(m_yaw * DEG2RAD) * cos(m_pitch * DEG2RAD));
  m_front.normalize();

  m_right = QVector3D::crossProduct(m_front, m_worldUp);
  m_right.normalize();

  m_up = QVector3D::crossProduct(m_right, m_front);
  m_up.normalize();
}