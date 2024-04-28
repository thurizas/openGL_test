#ifndef _glwindow_h_
#define _glwindow_h_


#include <QWindow>
#include <QOpenGLFunctions>

class QOpenGLContext;
class QOpenGLPaintDevice;

class glwindow : public QWindow, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  explicit glwindow(QWindow* parent = nullptr);
  ~glwindow();

  virtual void initialize();
  virtual void render(QPainter* painter);
  virtual void render();

  void setAnimating(bool animating);

public slots:
  void renderLater();
  void renderNow();

protected:
  bool event(QEvent* evt) override;
  void exposeEvent(QExposeEvent* evt) override;

private:
  bool m_animating = false;

  QOpenGLContext* m_context = nullptr;
  QOpenGLPaintDevice* m_device = nullptr;
};

#endif

