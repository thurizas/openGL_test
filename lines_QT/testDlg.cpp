#include "testDlg.h"
#include "GLDisplay.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include <QDebug>


testDlg::testDlg(QWidget* p) : QDialog(p)
{
  // setup the OpenGL surface and context...
  m_fmt = new QSurfaceFormat();
  m_fmt->setDepthBufferSize(24);
  m_fmt->setStencilBufferSize(8);
  m_fmt->setMajorVersion(3);
  m_fmt->setMinorVersion(3);
  m_fmt->setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(*m_fmt);
  setupUI();
}

testDlg::~testDlg()
{

}

void testDlg::setupUI()
{
  this->resize(800, 600);
  this->setWindowTitle("dialog test");

  QVBoxLayout* vlayout = new QVBoxLayout(this);

  m_display = new GLDisplay();
  m_display->resize(800, 580);

  QHBoxLayout* hlayout = new QHBoxLayout();
  QSpacerItem* spacer = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QPushButton* btnOK = new QPushButton();
  btnOK->setText("OK");
  QPushButton* btnCancel = new QPushButton();
  btnCancel->setText("Cancel");
  hlayout->addItem(spacer);
  hlayout->addWidget(btnOK);
  hlayout->addWidget(btnCancel);

  QHBoxLayout* controlLayout = new QHBoxLayout();
  QLabel* label1 = new QLabel();
  label1->setText("Position:       ");
  QLabel* label2 = new QLabel();
  label2->setText("Polar angle:    ");
  QLabel* label3 = new QLabel();
  label3->setText("Azimuthal angle:");

  m_XCoord = new QDoubleSpinBox();
  m_XCoord->setDecimals(2);
  m_XCoord->setSingleStep(10);
  m_XCoord->setRange(0.0f, 100.0f);
  m_YCoord = new QDoubleSpinBox();
  m_YCoord->setDecimals(2);
  m_YCoord->setSingleStep(10);
  m_YCoord->setRange(0.0f, 100.0f);
  m_ZCoord = new QDoubleSpinBox();
  m_ZCoord->setDecimals(2);
  m_ZCoord->setSingleStep(10);
  m_ZCoord->setRange(0.0f, 100.0f);
  m_polar = new QDoubleSpinBox();
  m_polar->setDecimals(2);
  m_polar->setRange(-90.0f, 90.0f);
  m_azimuthal = new QDoubleSpinBox();
  m_azimuthal->setDecimals(2);
  m_azimuthal->setRange(0.0f, 360.0f);

  controlLayout->addWidget(label1);
  controlLayout->addWidget(m_XCoord);
  controlLayout->addWidget(m_YCoord);
  controlLayout->addWidget(m_ZCoord);

  controlLayout->addWidget(label2);
  controlLayout->addWidget(m_polar);
  controlLayout->addWidget(label3);
  controlLayout->addWidget(m_azimuthal);

  vlayout->addWidget(m_display);
  vlayout->addLayout(controlLayout);
  vlayout->addLayout(hlayout);

  connect(btnOK, &QPushButton::clicked, this, &testDlg::onOK);
  connect(btnCancel, &QPushButton::clicked, this, &testDlg::onCancel);
  connect(m_XCoord, &QDoubleSpinBox::valueChanged, this, &testDlg::onPositionChanged);
  connect(m_YCoord, &QDoubleSpinBox::valueChanged, this, &testDlg::onPositionChanged);
  connect(m_ZCoord, &QDoubleSpinBox::valueChanged, this, &testDlg::onPositionChanged);
  connect(m_polar, &QDoubleSpinBox::valueChanged, this, &testDlg::onPolarChanged);
  connect(m_azimuthal, &QDoubleSpinBox::valueChanged, this, &testDlg::onAzimuthalChanged);
}

void testDlg::onPositionChanged(double )
{
  qDebug() << "in onPositionChanged";
}

void testDlg::onPolarChanged(double angle)
{
  qDebug() << "in onPolarChanged: " << angle;
}

void testDlg::onAzimuthalChanged(double angle)
{
  qDebug() << "in onAzimuthalChanged: " << angle;
}


void testDlg::onOK()
{
  QDialog::accept();
}

void testDlg::onCancel()
{
  QDialog::reject();
}
