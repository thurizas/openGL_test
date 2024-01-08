#ifndef _GLDisplay_h_
#define _GLDisplay_h_

#include "GLShaders.h"
#include "camera.h"
#include "glObject.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <qdialog.h>

#include <QMatrix4x4>

class QSurfaceFormat;

class GLDisplay : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
  GLDisplay(QWidget* parent = nullptr);
  ~GLDisplay();

  Camera* getCamera() { return &m_theCamera; }

protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;

private:
  QMatrix4x4             m_projection;
  QMatrix4x4             m_view;
  Camera                 m_theCamera;
  std::vector<glObject*> m_objects;
};



#endif
