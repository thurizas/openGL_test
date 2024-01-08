#include "GLShaders.h"

#include <cstdio>
#include <cstdlib>

glslShader::glslShader(QOpenGLFunctions_3_3_Core* pfncts) : m_fncts(pfncts)
{

}

glslShader::~glslShader()
{
  clearShader();
}

void glslShader::createFromStrings(const char* vCode, const char* fCode, const char* gCode)
{
  compileShader(vCode, fCode, gCode);
}


void glslShader::createFromFiles(const char* vFile, const char* fFile, const char* gFile)
{
  std::string   vCode = "";
  std::string   fCode = "";
  std::string   gCode = "";
  try
  {
    if (nullptr != vFile) vCode = readFile(vFile);
    if (nullptr != fFile) fCode = readFile(fFile);
    if (nullptr != gFile) gCode = readFile(gFile);

    if ((vCode == "") || (fCode == ""))
    {
      fprintf(stderr, "failed to read either %s shader\n", ((vCode == "") ? "vertex" : "fragment"));
    }
    else
    {
      compileShader(vCode.c_str(), fCode.c_str(), ((gCode == "") ? nullptr : gCode.c_str()));
    }
  }
  catch (std::exception& exc)
  {
    qDebug() << "exception hit";
    qDebug() << exc.what();
  }

}



std::string glslShader::readFile(const char* fileName)
{
  std::string    contents = "";
  std::ifstream  ifs(fileName, std::ios::in);

  if (ifs.is_open())
  {
    while (!ifs.eof())
    {
      std::string  line = "";
      std::getline(ifs, line);
      contents.append(line);
    }

    ifs.close();
  }
  else
  {
    throw std::system_error(errno, std::system_category(), "failed to open: " + std::string(fileName));
  }

  return contents;
}

void glslShader::compileShader(const char* vCode, const char* fCode, const char* gCode)
{
  m_shaderID = m_fncts->glCreateProgram();

  if (m_shaderID != -1)
  {
    addShader(m_shaderID, vCode, GL_VERTEX_SHADER);
    addShader(m_shaderID, fCode, GL_FRAGMENT_SHADER);
    if (nullptr != gCode) addShader(m_shaderID, gCode, GL_GEOMETRY_SHADER);

    GLint  result = -1;
    GLchar eLog[1024] = { 0 };

    m_fncts->glValidateProgram(m_shaderID);
    m_fncts->glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
    if (result)
    {
      m_fncts->glValidateProgram(m_shaderID);
      m_fncts->glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
      if (result)
      {
        m_uProjection = m_fncts->glGetUniformLocation(m_shaderID, "projection");
        m_uView = m_fncts->glGetUniformLocation(m_shaderID, "view");
        m_uModel = m_fncts->glGetUniformLocation(m_shaderID, "model");
      }
      else
      {
        m_fncts->glGetProgramInfoLog(m_shaderID, sizeof(eLog), nullptr, eLog);
        fprintf(stderr, "failed to validate shader program: '%s'\n", eLog);
      }
    }
    else
    {
      m_fncts->glGetProgramInfoLog(m_shaderID, sizeof(eLog), nullptr, eLog);
      fprintf(stderr, "failed to link shader program: '%s'\n", eLog);
    }
  }
  else
  {
    fprintf(stderr, "error creating shader program");
  }
}

void glslShader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
  GLuint theShader = m_fncts->glCreateShader(shaderType);

  const GLchar* theCode[1];
  theCode[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);

  m_fncts->glShaderSource(theShader, 1, theCode, codeLength);
  m_fncts->glCompileShader(theShader);

  GLint    result = -1;
  GLchar   eLog[1024] = { 0 };

  m_fncts->glGetProgramiv(theShader, GL_COMPILE_STATUS, &result);
  if (result)
  {
    m_fncts->glAttachShader(theProgram, theShader);
  }
  else
  {
    m_fncts->glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
    fprintf(stderr, "failed to compile %d shader, error is: '%s'\n", theShader, eLog);
  }
}

void glslShader::useShader()
{
  m_fncts->glUseProgram(m_shaderID);
}

void glslShader::clearShader()
{
  if (0 != m_shaderID)
  {
    m_fncts->glDeleteShader(m_shaderID);
    m_shaderID = 0;
  }

  m_uModel = m_uView = m_uProjection = 0;
}
