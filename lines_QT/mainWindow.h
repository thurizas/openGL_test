#pragma once

#include <QMainWindow>

class QAction;

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private slots:
  void onTest();

private:
  QAction* m_actTest;

  void     setupUI();
  void     setupActions();
  void     setupMenus();

};
