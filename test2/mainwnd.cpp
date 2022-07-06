#include "mainWnd.h"
#include "openGLDisplay.h"
//#include "line.h"

#include <cstdio>
#include <cstdlib>

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
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

  QFont  font;
  font.setFamily("Courier New");
  font.setPointSize(12);

  if (this->objectName().isEmpty())
    this->setObjectName("mainWndClass");
  this->resize(640, 480);
  this->setWindowTitle("OpenGL test 2");

  centralWidget = new QWidget(this);
  centralWidget->setObjectName(QString::fromUtf8("centralWidget"));


  // build openGl display ...
  m_glwindow = new openGLDisplay(centralWidget);
  m_glwindow->setObjectName("glwindow");
  m_glwindow->setMinimumSize(QSize(600, 380));
  //this->setCentralWidget(m_glwindow);

  // build x-rotation control...
  QHBoxLayout* xLayout = new QHBoxLayout();
  xLayout->setSpacing(6);
  xLayout->setContentsMargins(10, -1, 10, -1);
  xLayout->setObjectName(QString::fromUtf8("xLayout"));
  QLabel* label1 = new QLabel(centralWidget);
  label1->setFont(font);
  label1->setObjectName("label1");
  label1->setText("x-rotation:");
  
  m_xRotValue = new QSlider(centralWidget);
  m_xRotValue->setOrientation(Qt::Horizontal);
  m_xRotValue->setObjectName("m_xRotValue");
  m_xRotValue->setTickInterval(10);
  m_xRotValue->setTickPosition(QSlider::TicksBothSides);
  m_xRotValue->setMaximum(360);

  m_spinX = new QSpinBox(centralWidget);
  m_spinX->setObjectName("m_spinX");
  m_spinX->setMaximum(360);
  m_spinX->setFont(font);

  xLayout->addWidget(label1);
  xLayout->addWidget(m_xRotValue);
  xLayout->addWidget(m_spinX);

  // build y-rotation control...
  QHBoxLayout* yLayout = new QHBoxLayout();
  yLayout->setSpacing(6);
  yLayout->setContentsMargins(10, -1, 10, -1);
  yLayout->setObjectName("yLayout");
  QLabel* label2 = new QLabel(centralWidget);
  label2->setFont(font);
  label2->setObjectName("label2");
  label2->setText("y-rotation:");

  m_yRotValue = new QSlider(centralWidget);
  m_yRotValue->setOrientation(Qt::Horizontal);
  m_yRotValue->setObjectName("m_yRotValue");
  m_yRotValue->setTickInterval(10);
  m_yRotValue->setTickPosition(QSlider::TicksBothSides);
  m_yRotValue->setMaximum(360);

  m_spinY = new QSpinBox(centralWidget);
  m_spinY->setFont(font);
  m_spinY->setMaximum(360);
  m_spinY->setObjectName("m_spinY");

  yLayout->addWidget(label2);
  yLayout->addWidget(m_yRotValue);
  yLayout->addWidget(m_spinY);
  
  // build z-rotation control...
  QHBoxLayout* zLayout = new QHBoxLayout();
  zLayout->setSpacing(6);
  zLayout->setContentsMargins(10, -1, 10, 10);
  zLayout->setObjectName("horizontalLayout_3");
  QLabel* label3 = new QLabel(centralWidget);
  label3->setFont(font);
  label3->setObjectName("label3");
  label3->setText("z-rotation:");

  m_zRotValue = new QSlider(centralWidget);
  m_zRotValue->setObjectName(QString::fromUtf8("m_zRotValue"));
  m_zRotValue->setTickInterval(10);
  m_zRotValue->setTickPosition(QSlider::TicksBothSides);
  m_zRotValue->setMaximum(360);
  m_zRotValue->setOrientation(Qt::Horizontal);

  m_spinZ = new QSpinBox(centralWidget);
  m_spinZ->setFont(font);
  m_spinZ->setMaximum(360);
  m_spinZ->setObjectName(QString::fromUtf8("m_spinZ"));

  zLayout->addWidget(label3);
  zLayout->addWidget(m_zRotValue);
  zLayout->addWidget(m_spinZ);

  verticalLayout = new QVBoxLayout(centralWidget);
  verticalLayout->setSpacing(6);
  verticalLayout->setContentsMargins(11, 11, 11, 11);
  verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
  verticalLayout->setContentsMargins(0, 0, 0, 0);
  
  verticalLayout->addWidget(m_glwindow);
  verticalLayout->addLayout(xLayout);
  verticalLayout->addLayout(yLayout);
  verticalLayout->addLayout(zLayout);

  this->setCentralWidget(centralWidget);
  // build and set menu bar...
  m_menuBar = new QMenuBar(this);
  m_menuBar->setObjectName("menuBar");
  m_menuBar->setGeometry(QRect(0, 0, 208, 21));
  this->setMenuBar(m_menuBar);

  // setup connections
  // TODO: (1) when slider value changes --> update spin-box value
  connect(m_xRotValue, SIGNAL(sliderReleased()), this, SLOT(onXSliderChanged()));
  connect(m_yRotValue, SIGNAL(sliderReleased()), this, SLOT(onYSliderChanged()));
  connect(m_zRotValue, SIGNAL(sliderReleased()), this, SLOT(onZSliderChanged()));
  // TODO: (2) when spin-box value changes -- update slider position
  connect(m_spinX, SIGNAL(valueChanged(int)), this, SLOT(onXRotChanged(int)));
  connect(m_spinY, SIGNAL(valueChanged(int)), this, SLOT(onYRotChanged(int)));
  connect(m_spinZ, SIGNAL(valueChanged(int)), this, SLOT(onZRotChanged(int)));
  // TODO: (3) when either slider or spit-box changes call set*Rotation
}

void mainWnd::setupMenu()
{
  QMenu* fileMenu = m_menuBar->addMenu("exit");
  fileMenu->addAction(m_fileExit);
}

void mainWnd::setupActions()
{
  m_fileExit = new QAction("eXit", this);
  m_fileExit->setShortcut(QKeySequence::Quit);
  connect(m_fileExit, SIGNAL(triggered()), this, SLOT(onExit()));
}

void mainWnd::onExit()
{
  fprintf(stderr, "[mainWnd::onExit]\n");
}

void mainWnd::onXSliderChanged()
{
  int x = m_xRotValue->value();
  m_spinX->setValue(x);
}

void mainWnd::onYSliderChanged()
{
  int y = m_yRotValue->value();
  m_spinY->setValue(y);
}

void mainWnd::onZSliderChanged()
{
  int z = m_zRotValue->value();
  m_spinZ->setValue(z);
}

void mainWnd::onXRotChanged(int v)
{
  m_xRotValue->setValue(v);
  m_glwindow->setXRotation(v);
}

void mainWnd::onYRotChanged(int v)
{
  m_yRotValue->setValue(v);
  m_glwindow->setYRotation(v);
}

void mainWnd::onZRotChanged(int v)
{
  m_zRotValue->setValue(v);
  m_glwindow->setZRotation(v);
}


