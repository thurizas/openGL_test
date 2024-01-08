#ifndef _camera_h_
#define _camera_h_

#include <QMatrix4x4>
#include <QVector3D>

#include <QOpenGlFunctions_3_3_core>

class Camera 
{
public:
  Camera();
  Camera(QVector3D pos, QVector3D up, float yaw, float pitch, float moveSpd, float turnSpd);
  ~Camera();

  QMatrix4x4 calcViewMatrix();

private:
  QMatrix4x4    m_lookAt;

  QVector3D     m_pos;
  QVector3D     m_front;
  QVector3D     m_up;
  QVector3D     m_right;
  QVector3D     m_worldUp;

  float         m_yaw;
  float         m_pitch;

  float         m_moveSpd;
  float         m_turnSpd;

  void          update();
};

#endif;