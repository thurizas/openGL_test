#include "GLDisplay.h"
#include "glLine.h"


#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QtOpenGL/QOpenGLVersionFunctionsFactory>
#include <QSurfaceFormat>

#include <QDebug>

GLDisplay::GLDisplay(QWidget* p) : QOpenGLWidget(p)
{
  m_theCamera = Camera(QVector3D(3.0, 3.0, 3.0), QVector3D(0.0, 1.0, 0.0), 0.0, 0.0, 5.0f, 5.0f);
}

GLDisplay::~GLDisplay()
{

}

void GLDisplay::initializeGL()
{
  if (initializeOpenGLFunctions())
  {
    QOpenGLContext* pContext = QOpenGLContext::currentContext();
    auto fncts = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>(pContext);

    try
    {
      // build a line model....    
      //std::vector<QVector3D> l = { QVector3D(-1.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f) };
      //line* pline = new line(&l, R"(./shaders/vline.glsl)", R"(./shaders/fline.glsl)", fncts);
      //float clr[] = { 1.0f, 0.0f, 0.0f };
      //pline->color(clr, 3);
      //m_objects.push_back(pline);
      line* l1 = new line(QVector3D(-1.0, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), fncts);
      l1->setColor(QVector3D(1.0f, 0.0f, 0.0f));
      m_objects.push_back(l1);
    }
    catch (const std::exception* exc)
    {
      qDebug() << exc->what();
    }
  }
  else
  {
    QMessageBox::warning(nullptr, "GL error", "failed to initialize GL Functions");
  }
}

void GLDisplay::resizeGL(int w, int h)
{
  m_projection.setToIdentity();
  m_projection.perspective(49.0f, w / (float)h, 0.01f, 100.0f);
}

void GLDisplay::paintGL()
{

  m_view = m_theCamera.calcViewMatrix();
  QMatrix4x4 VP = m_projection * m_view;
  
  for (glObject* m : m_objects)
  {
    m->setMVP(m_projection * m_view);
    m->draw();
  }
}