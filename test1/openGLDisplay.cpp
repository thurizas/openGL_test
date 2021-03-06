#include "openGLDisplay.h"

#include <QMouseEvent>

#include <QOpenGLBuffer>
#include <QOpenGlVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>



static const char* glslVertex =
"#version 150\n"
"in vec4 vertex;\n"
"in vec3 normal;\n"
"out vec3 vert;\n"
"out vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
"   gl_Position = projMatrix * mvMatrix * vertex;\n"
"}\n";

static const char* glslFragment=
"#version 150\n"
"in highp vec3 vert;\n"
"in highp vec3 vertNormal;\n"
"out highp vec4 fragColor;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";




openGLDisplay::openGLDisplay(QWidget* parent) : QOpenGLWidget(parent), m_pFncts(nullptr), m_lightPos(0), m_projMatrixLoc(0), m_mvMatrixLoc(0), m_normalMatrixLoc(0), m_program(0), m_shader(0)//, m_texture(0)
{
  fprintf(stderr, "[openGLDisplay::openGLDisplay]:\n");

  m_xRot = m_yRot = m_zRot = 0;

  // not necessarly required, but useful for finer-grained control over surface
  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setStencilBufferSize(8);
  fmt.setVersion(3, 3);
  fmt.setProfile(QSurfaceFormat::CoreProfile);
  this->setFormat(fmt);   

  // set up our vertex data....
  m_vertex.push_back(-0.5f);                              // x coordinate of lower left point
  m_vertex.push_back(-0.5f);
  m_vertex.push_back(0.0f);
  m_vertex.push_back(0.5f);                               // x coordinate of lower right point
  m_vertex.push_back(-0.5f);
  m_vertex.push_back(0.0f);
  m_vertex.push_back(0.0f);                               // x coordinate of upper point
  m_vertex.push_back(0.5f);
  m_vertex.push_back(0.0f);

}

openGLDisplay::~openGLDisplay()
{
  fprintf(stderr, "[openGLDisplay::~openGLDisplay]:");
  teardownGL();
}

QSize openGLDisplay::minimumSizeHint() const
{
  return QSize(50, 50);
}

QSize openGLDisplay::sizeHint() const
{
  return QSize(400, 400);
}

void openGLDisplay::setXRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != m_xRot) {
    m_xRot = angle;
    emit xRotationChanged(angle);
    update();
  }
}

void openGLDisplay::setYRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != m_yRot) {
    m_yRot = angle;
    emit yRotationChanged(angle);
    update();
  }
}

void openGLDisplay::setZRotation(int angle)
{
  normalizeAngle(angle);
  if (angle != m_zRot) {
    m_zRot = angle;
    emit zRotationChanged(angle);
    update();
  }
}


void openGLDisplay::initializeGL()
{
  fprintf(stderr, "[openGLDisplay::initializeGL]:\n");

  connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &openGLDisplay::teardownGL);


  if (initializeOpenGLFunctions())
  {  
    printContextInfo();
    m_pFncts = QOpenGLContext::currentContext()->versionFunctions <QOpenGLFunctions_3_3_Core>();
    fprintf(stderr, "  successfully initialized OpenGLFunctions, function pointer is: 0x%08p\n", m_pFncts);
    
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, glslVertex);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, glslFragment);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal",1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPos = m_program->uniformLocation("lightPos");

    m_vao.create();
    if (m_vao.isCreated())
      m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(m_vertex.constData(), m_vertex.count() * sizeof(GLfloat));

    setupVertexAttribs();

    // set up fixed position camera....
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // set up fixed position light
    m_light = QVector3D(0, 0, 70);
    m_program->setUniformValue(m_lightPos, m_light);

    m_program->release();
  }
  else
  {
    fprintf(stderr, "  failed to initialize OpenGLFunctions \n");
  }

  glClearColor(0.0, 128.0 / 255.0, 0.0f, 0.0f);
}

void openGLDisplay::setupVertexAttribs()
{
  m_vbo.bind();
  GLCall(m_pFncts, m_pFncts->glEnableVertexAttribArray(0))
  GLCall(m_pFncts, m_pFncts->glEnableVertexAttribArray(1))
  GLCall(m_pFncts, m_pFncts->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr))
  GLCall(m_pFncts, m_pFncts->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat))))
  GLCall(m_pFncts, m_vbo.release())
}

void openGLDisplay::resizeGL(int w, int h)
{
  fprintf(stderr, "[openGLDisplay::resizeGL]:\n");

  m_proj.setToIdentity();
  m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);

}

void openGLDisplay::paintGL()
{
  fprintf(stderr, "[openGLDisplay::paintGL]:\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  m_world.setToIdentity();
  m_world.scale(0.5f);

  QOpenGLVertexArrayObject::Binder       vaoBinder(&m_vao);   
  m_program->bind();
  m_program->setUniformValue(m_projMatrixLoc, m_proj);
  m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
  QMatrix3x3 normMatrix = m_world.normalMatrix();
  m_program->setUniformValue(m_normalMatrixLoc, normMatrix);

  glDrawArrays(GL_TRIANGLES, 0, 3);                             
}





void openGLDisplay::teardownGL()
{
  fprintf(stderr, "[openGLDisplay::teardownGL]:\n");

  if (m_program != nullptr)
  {
    makeCurrent();
    //delete m_texture;
    delete m_shader; m_shader = nullptr;
    delete m_program; m_program = nullptr;

    m_vbo.destroy();
    m_vao.destroy();
    doneCurrent();
  }
}


void openGLDisplay::printContextInfo()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  //Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  //Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  fprintf(stderr, "Type: %s\n  Version: %s\n  Profile: %s\n", glType.toStdString().c_str(), glVersion.toStdString().c_str(), glProfile.toStdString().c_str());
}


void openGLDisplay::mousePressEvent(QMouseEvent* event)
{
  m_lastPt = event->pos();
}

void openGLDisplay::mouseMoveEvent(QMouseEvent* event)
{
  int dx = event->x() - m_lastPt.x();
  int dy = event->y() - m_lastPt.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(m_xRot + 8 * dy);
    setYRotation(m_yRot + 8 * dx);
  }
  else if (event->buttons() & Qt::RightButton) {
    setXRotation(m_xRot + 8 * dy);
    setZRotation(m_zRot + 8 * dx);
  }
  m_lastPt = event->pos();
}
