#include "GLDisplay.h"
#include "glLine.h"


#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QtOpenGL/QOpenGLVersionFunctionsFactory>
#include <QSurfaceFormat>

#include <QDebug>

GLDisplay::GLDisplay(QWidget* p) : QOpenGLWidget(p), m_pCamera(nullptr)
{
  //m_theCamera = Camera(QVector3D(3.0, 3.0, 3.0), QVector3D(0.0, 1.0, 0.0), 0.0, 0.0, 5.0f, 5.0f);
  m_pCamera = new camera();
}

GLDisplay::~GLDisplay()
{
  if (nullptr != m_pCamera) delete m_pCamera;
}

void GLDisplay::initializeGL()
{
  if (initializeOpenGLFunctions())
  {
    QOpenGLContext* pContext = QOpenGLContext::currentContext();
    auto fncts = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>(pContext);

    try
    {
      line* l1 = new line(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), fncts);
      l1->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

      line* l2 = new line(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), fncts);
      l2->setColor(glm::vec3(0.0f, 1.0f, 0.0f));

      line* l3 = new line(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), fncts);
      l3->setColor(glm::vec3(0.0f, 0.0f, 1.0f));

      m_objects.push_back(l1);
      m_objects.push_back(l2);
      m_objects.push_back(l3);
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
  m_projection = glm::mat4(1.0);
  m_projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
}

void GLDisplay::paintGL()
{
  m_pCamera->pos(glm::vec3(3.0f, 3.0f, 3.0f));
  glm::vec3 pos = m_pCamera->pos();
  m_view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 /* QMatrix4x4 */ VP = m_projection * m_view;

  
  for (glObject* m : m_objects)
  {
    m->setMVP(m_projection * m_view);
    m->draw();
  }
}