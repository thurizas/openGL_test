#ifndef _mainWnd_h_
#define _mainWnd_h_

#include <QMainWindow>
#include <QObject>

class openGLDisplay;
class QMenuBar;
class QAction;

class mainWnd : public QMainWindow
{
  Q_OBJECT
public:
  mainWnd();
  virtual ~mainWnd();

private slots:
  //void  onAddVLine();
  //void  onAddHLine();

private:
  openGLDisplay* m_glwindow;
  QMenuBar*      m_menuBar;
  QAction*       m_addVLine;
  QAction*       m_addHLine;

  void setupUI();
  void setupMenu();
  void setupActions();
};


#endif
