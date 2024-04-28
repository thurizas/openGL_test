#include <GL/glew.h>

#include <cstdint>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<iterator>

#include "util.h"

std::string shaderFromFile(const char* name)
{
  std::string contents = "";

  std::ifstream in(name, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::beg);                    // move to begining
    in.seekg(0, std::ios::end);                    // move to end;

    contents.resize((size_t)in.tellg());           // resize string to length of file

    in.seekg(0, std::ios::beg);                    // move back to beginning
    in.read(&contents[0], contents.size());        // read file
    in.close();
  }
  return contents;
}


/************************************************************************************************************************
 * function  : shaderFromFile
 *
 * abstract  : read a file and returns the shader source as a character buffer that can be passed to glCompileShader.  This
 *             is an overloaded form of the above function
 *
 * parameters: name -- [in] a null-terminated character array containing the path for the shader file to open.
 *             souce -- [out] pointer to a character array that will receive the shader source.  If there is an exist 
 *                      values in the character array, they will be deleted prior to reading the shader source
 *
 * returns   : boolean - return true if the file was successfully read. other it return false.
 *
 * written   : Aug 2022 (GKHuber)
************************************************************************************************************************/
bool shaderFromFile(const char* name, char** source)
{
  bool bRet = true; 

  if (*source != nullptr)
  {
    delete* source;
    *source = nullptr;
  }

  std::ifstream in(name, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::beg);
    in.seekg(0, std::ios::end);

    size_t len = in.tellg();

    in.seekg(0, std::ios::beg);
    *source = new char[len+1];

    memset((void*)*source, '\0', len+1);

    in.read((*source), len);
  }
  else
  {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    bRet = false;
  }

  return bRet;
}

/************************************************************************************************************************
 * function :  checkShader
 *
 * abstract  : checks the compilation status of compiling a shader.  If the compilation fails, then it calls 
 *             printShaderLog to provide error details
 *
 * parameters: shader -- [in] the shader id, as returned from glCreateShader
 *
 * returns   : boolean - true if compilation was successful, false otherwise
 *
 * written   : Aug 2022 (GKHuber)
************************************************************************************************************************/
bool checkShader(GLuint shader)
{
  GLint compilationStatus = -1;
  bool  bRet = false;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);
  if (GL_FALSE == compilationStatus)
  {
    printShaderLog(shader);
  }
  else
  {
    bRet = true;
  }

  return bRet;
}

/************************************************************************************************************************
 * function :  checkLink
 *
 * abstract  : checks the linking status of linking fragments into a program.  If the compilation fails, then it calls
 *             printProgramLog to provide error details
 *
 * parameters: program -- [in] the program id, as returned from glCreateProgram
 *
 * returns   : boolean - true if compilation was successful, false otherwise
 *
 * written   : Aug 2022 (GKHuber)
************************************************************************************************************************/
bool checkLink(GLuint program)
{
  GLint linkStatus = -1;
  bool  bRet = false;

  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  if (GL_FALSE == linkStatus)
  {
    printProgramLog(program);
  }
  else
  {
    bRet = true;
  }

  return bRet;
}

/************************************************************************************************************************
 * function  : printShaderLog
 *
 * abstract  : This function prints the contents of the shader compile log to standard out.  This function is only called
 *             if checkShader detectes an error.  As such this function is declared as `static'
 *
 * parameters: shader -- [in]  the shader id, as returned from glCreateShader
 *
 * returns   : void.
 *
 * written   : Aug 2022 (GKHuber)
************************************************************************************************************************/
void printShaderLog(GLuint shader)
{
  GLint maxLen = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);

  std::vector<GLchar> infoLog(maxLen);
  glGetShaderInfoLog(shader, maxLen, &maxLen, &infoLog[0]);

  std::copy(infoLog.begin(), infoLog.end(), std::ostream_iterator<GLchar>(std::cout, ""));

}

/************************************************************************************************************************
 * function  : printProgramLog
 *
 * abstract  : This function prints the contents of the program link log to standard out.  This function is only called
 *             if checkLink detects an error.  As such this function is declared as `static'
 *
 * parameters: program -- [in] the program id, as returned from glCreateProgram
 *
 * returns   : void
 *
 * written   : Aug 2022 (GKHuber)
************************************************************************************************************************/
static void printProgramLog(GLuint program)
{
  GLint maxLen = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);

  std::vector<GLchar> infoLog(maxLen);
  glGetProgramInfoLog(program, maxLen, &maxLen, &infoLog[0]);

  std::copy(infoLog.begin(), infoLog.end(), std::ostream_iterator<GLchar>(std::cout, ""));
}