#include "mainWnd.h"
#include "openGLDisplay.h"
//#include "line.h"

#include <cstdio>
#include <cstdlib>

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

mainWnd::mainWnd() : QMainWindow()
{
  fprintf(stderr, "[mainWnd::mainWnd] constructing the main window\n");
  setupUI();
  setupActions();
  setupMenu();
}

mainWnd::~mainWnd()
{
  fprintf(stderr, "[mainWnd::~mainWnd] destorying main window object\n");
}

void mainWnd::setupUI()
{
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout;

  if (this->objectName().isEmpty())
    this->setObjectName("mainwindow");

  this->setWindowTitle("OpenGL Test");
  this->resize(640, 480);

  m_glwindow = new openGLDisplay(this);
  m_glwindow->setObjectName("glwindow");
  this->setCentralWidget(m_glwindow);

  m_menuBar = new QMenuBar(this);
  m_menuBar->setObjectName("mainMenuBar");
  this->setMenuBar(m_menuBar);
}

void mainWnd::setupMenu()
{
  //QMenu* editMenu = m_menuBar->addMenu("Edit");
  //editMenu->addAction(m_addVLine);
  //editMenu->addAction(m_addHLine);
}

void mainWnd::setupActions()
{
  //m_addVLine = new QAction("V-line", this);
  //connect(m_addVLine, SIGNAL(triggered()), this, SLOT(onAddVLine()));

  //m_addHLine = new QAction("H-line", this);
  //connect(m_addHLine, SIGNAL(triggered()), this, SLOT(onAddHLine()));
}

//void mainWnd::onAddVLine()
//{
//  fprintf(stderr, "[mainWnd::onAddVLine - adding vertical line\n");
//  m_glwindow->addItem(geoobject::type::VLINE);
//}
//
//void mainWnd::onAddHLine()
//{
//  fprintf(stderr, "[mainWnd::onAddHLine - adding horizontal line\n");
//  m_glwindow->addItem(geoobject::type::HLINE);
//}
