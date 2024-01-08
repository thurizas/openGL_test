#ifndef _testDlg_h_
#define _testDlg_h_


#include "GLDisplay.h"
#include <QDialog>

class QDoubleSpinBox;

class testDlg : public QDialog
{
public:
  testDlg(QWidget* parent = nullptr);
  ~testDlg();

private slots:
  void onPositionChanged(double);
  void onPolarChanged(double);
  void onAzimuthalChanged(double);
  void onOK();
  void onCancel();

private:
  void setupUI();

  GLDisplay*         m_display = nullptr;
  QDoubleSpinBox*    m_XCoord = nullptr;
  QDoubleSpinBox*    m_YCoord = nullptr;
  QDoubleSpinBox*    m_ZCoord = nullptr;
  QDoubleSpinBox*    m_polar = nullptr;
  QDoubleSpinBox*    m_azimuthal = nullptr;

  QSurfaceFormat*    m_fmt = nullptr;
  QOpenGLContext*    m_context = nullptr;
};

#endif