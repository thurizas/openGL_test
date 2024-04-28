#include "shader.h"

#include <fstream>
#include <string>

CShader::CShader()
{
  shaderID = 0;
  uModel = 0;
  uProjection = 0;
}

CShader::~CShader()
{
  clearShader();
}

void CShader::createFromStrings(const char* vertex, const char* fragment)
{
  compileShader(vertex, fragment);
}

void CShader::createFromFiles(const char* vertex, const char* fragment)
{
  std::string vString = readFile(vertex);
  std::string fString = readFile(fragment);

  compileShader(vString.c_str(), fString.c_str());
}

std::string CShader::readFile(const char* name)
{
  std::string content = "";
  std::ifstream fileStream(name, std::ios::in);

  if (!fileStream.is_open())
  {
    std::cerr << "[-] failed to read: " << name << ". File does not exist" << std::endl;
  }
  else
  {
    std::string line = "";
    while (!fileStream.eof())
    {
      std::getline(fileStream, line);
      content.append(line + "\n");
    }

    fileStream.close();
  }

  return content;
}


void CShader::compileShader(const char* vertex, const char* fragment)
{
  shaderID = glCreateProgram();

  if (shaderID)
  {
    addShader(shaderID, vertex, GL_VERTEX_SHADER);
    addShader(shaderID, fragment, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (result)
    {
      glValidateProgram(shaderID);
      glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
      if (result)
      {
        uProjection = glGetUniformLocation(shaderID, "projection");
        uModel = glGetUniformLocation(shaderID, "model");
      }
      else
      {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cerr << "[-] error validating program: " << eLog << std::endl;
      }
    }
    else
    {
      glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
      std::cerr << "[-] error linking program: " << eLog << std::endl;
    }
  }
  else
  {
    std::cerr << "[-] error creating CShader program" << std::endl;
  }
}


void CShader::addShader(GLuint theProgram, const char* code, GLenum CShaderType)
{
  GLuint theShader = glCreateShader(CShaderType);

  const GLchar* theCode[1];
  theCode[0] = code;

  GLint codeLen[1];
  codeLen[0] = (GLint)strlen(code);

  glShaderSource(theShader, 1, theCode, codeLen);
  glCompileShader(theShader);

  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (result)
  {
    glAttachShader(theProgram, theShader);
  }
  else
  {
    glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
    std::cerr << "[-] error compiling the " << CShaderType << " CShader.  Error: " << eLog << std::endl;
  }


}




void CShader::useShader()
{
  glUseProgram(shaderID);
}

void CShader::clearShader()
{
  if (shaderID != 0)
  {
    glDeleteProgram(shaderID);
    shaderID = 0;
  }

  uModel = 0;
  uProjection = 0;
}