#ifndef _mainWnd_h_
#define _mainWnd_h_

#include <QMainWindow>
#include <QObject>

class openGLDisplay;
class QSlider;
class QSpinBox;
class QMenuBar;
class QAction;

class mainWnd : public QMainWindow
{
  Q_OBJECT
public:
  mainWnd();
  virtual ~mainWnd();

private slots:
  void onExit();
  void onXSliderChanged();
  void onYSliderChanged();
  void onZSliderChanged();
  void onXRotChanged(int);
  void onYRotChanged(int);
  void onZRotChanged(int);

private:
  // GUI components...
  QSlider*       m_xRotValue;
  QSlider*       m_yRotValue;
  QSlider*       m_zRotValue;
  QSpinBox*      m_spinX;
  QSpinBox*      m_spinY;
  QSpinBox*      m_spinZ;
  QMenuBar*      m_menuBar;

  openGLDisplay* m_glwindow;
  
  QAction*       m_fileExit;

  void setupUI();
  void setupMenu();
  void setupActions();
};


#endif
