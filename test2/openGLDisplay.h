#ifndef _opengldisplay_h_
#define _opengldisplay_h_

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGlVertexArrayObject>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMatrix3x3>

#include "common.h"
#include "tetrahedron.h"

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLShader;
class QMouseEvent;

class openGLDisplay : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

public:
  openGLDisplay(QWidget* parent = nullptr);
  ~openGLDisplay();

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

public slots:
  void setXRotation(int);
  void setYRotation(int);
  void setZRotation(int);

signals:
  void xRotationChanged(int);
  void yRotationChanged(int);
  void zRotationChanged(int);

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void mousePressEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;


private:
  void printContextInfo();
  void setupVertexAttribs();
  void teardownGL();

  QOpenGLFunctions_3_3_Core* m_pFncts;

  uint32_t                m_lightPos;         // uniform for light position
  uint32_t                m_projMatrixLoc;    // uniform location for project matrix
  uint32_t                m_mvMatrixLoc;      // uniform location for the model-view matrix
  uint32_t                m_normalMatrixLoc;  // uniform location for the nomal matrix
  QVector3D               m_light;            // vector representing where light is

  QMatrix4x4              m_camera;           // matrix defining the transformation on camera
  QMatrix4x4              m_proj;             // projection matrix, 
  QMatrix4x4              m_world;            // world view matrix;
  
  uint32_t                m_xRot;
  uint32_t                m_yRot;
  uint32_t                m_zRot;

  QPoint                  m_lastPt;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer            m_vbo;
  QOpenGLBuffer            m_ibo;            // index buffer object
  QOpenGLShaderProgram*    m_program;
  QOpenGLShader*           m_shader;

  tetrahedron              m_tetra;
};

#endif
