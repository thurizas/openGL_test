#ifndef _GLDisplay_h_
#define _GLDisplay_h_

#include "GLShaders.h"
#include "camera.h"
#include "glObject.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <qdialog.h>

//#include <QMatrix4x4>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class QSurfaceFormat;

class GLDisplay : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
  GLDisplay(QWidget* parent = nullptr);
  ~GLDisplay();

  camera* getCamera() { return m_pCamera; }

protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;

private:
  glm::mat4 /*QMatrix4x4*/ m_projection;
  glm::mat4 /*QMatrix4x4*/ m_view;
  camera*                  m_pCamera;
  std::vector<glObject*>   m_objects;
};



#endif
