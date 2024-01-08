#include "mainWindow.h"
#include "testDlg.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

mainWindow::mainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUI();
    setupActions();
    setupMenus();
}

mainWindow::~mainWindow()
{
}

void mainWindow::setupUI()
{
  this->setWindowTitle("OpenGL dialog test");
  this->resize(300, 100);
}

void mainWindow::setupActions()
{
  m_actTest = new QAction("test");
  connect(m_actTest, &QAction::triggered, this, &mainWindow::onTest);
}

void mainWindow::setupMenus()
{
  QMenu* testMenu = menuBar()->addMenu("test");
  testMenu->addAction(m_actTest);
}

void mainWindow::onTest()
{
  testDlg   dlg;
  dlg.exec();
}
