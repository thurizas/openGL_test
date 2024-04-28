#include <QGuiApplication>
#include <QSurfaceFormat>

#include "glwindow.h"

int main(int argc, char** argv)
{
  QGuiApplication theApp(argc, argv);

  QSurfaceFormat fmt;
  fmt.setSamples(16);

  glwindow  window;
  window.setFormat(fmt);
  window.resize(640, 480);
  window.show();

  window.setAnimating(true);

  return theApp.exec();
}