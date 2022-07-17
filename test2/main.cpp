#define LEAN_AND_MEAN
#include <Windows.h>

#include <QApplication>

#include <iostream>

#include "mainWnd.h"
#include "logger.h"


void allocConsole();

void cmdOut(char* msg)
{
  std::cout << msg << std::endl;
}

int main(int argc, char** argv)
{
  uint32_t  dbgLevel = 1;

  QApplication app(argc, argv);

  CLogger* pLogger = CLogger::getInstance();
  pLogger->setLevel(dbgLevel);
  pLogger->regOutDevice(0, cmdOut);
  
  allocConsole();

  mainWnd    mWindow;
  mWindow.show();
  int ret = app.exec();

  return ret;
}


// printing debugging information, status information to the consol window iscommon and helpful... except if you are brain-dead idiots  
// from Microsoft who disable this stuff So, lets fix this.  (taken from Adding Console I/O to a Win32 GUI App,  Windows Developer 
// Journal, Dec 1997; and updated from https://smacdo.com/programming/redirecting-standard-output-to-console-in-windows/)
void allocConsole()
{

  if (AllocConsole() == 0)                // Create the console window and set the window title.
  {
    // TODO : Handle error here. Use ::GetLastError() to get the error.
  }


  FILE* pNewStdout = nullptr;             // Redirect stdin, stdout and stderr  handles to the console window.
  FILE* pNewStderr = nullptr;
  FILE* pNewStdin = nullptr;

  ::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
  ::freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
  ::freopen_s(&pNewStdin, "CONIN$", "r", stdin);

  // Clear the error state for all of the C++ standard streams. Attempting to accessing the streams before they refer
  // to a valid target causes the stream to enter an error state. Clearing the error state will fix this problem,
  // which seems to occur in newer version of Visual Studio even when the console has not been read from or written
  // to yet.

  std::cout.clear();
  std::cerr.clear();
  std::cin.clear();

  std::wcout.clear();
  std::wcerr.clear();
  std::wcin.clear();
}
