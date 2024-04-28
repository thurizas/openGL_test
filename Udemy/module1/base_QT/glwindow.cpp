#include "glwindow.h"

#include <QOpenGLPaintDevice>
#include <QPainter>

glwindow::glwindow(QWindow* parent)
{
  setSurfaceType(QWindow::OpenGLSurface);
}


glwindow::~glwindow()
{

}

void glwindow::initialize() {} 


void glwindow::render(QPainter* painter)
{
  Q_UNUSED(painter);
}

void glwindow::render()
{
  if (m_device == nullptr)
  {
    m_device = new QOpenGLPaintDevice;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  m_device->setSize(size() * devicePixelRatio());
  m_device->setDevicePixelRatio(devicePixelRatio());

  QPainter painter(m_device);
  render(&painter);

}

void glwindow::renderLater()
{
  requestUpdate();
}


bool glwindow::event(QEvent* evt)
{
  switch (evt->type())
  {
  case QEvent::UpdateRequest:
    renderNow();
    return true;

  default:
    return QWindow::event(evt);
  }
}


  void glwindow::exposeEvent(QExposeEvent * evt)
  {
    Q_UNUSED(evt);

    if (isExposed())
      renderNow();
  }

  void glwindow::renderNow()
  {
    if (!isExposed())
      return;

    bool needsInitialize = false;

    if (!m_context) 
    {
      m_context = new QOpenGLContext(this);
      m_context->setFormat(requestedFormat());
      m_context->create();

      needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) 
    {
      initializeOpenGLFunctions();
      initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
      renderLater();
  }


  void glwindow::setAnimating(bool animating)
  {
    m_animating = animating;

    if (animating)
      renderLater();
  }




