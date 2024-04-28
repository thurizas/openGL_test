#include <cstdio>
#include <cstring>

#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "glfwWindow.h"
#include "util.h"
#include "shader.h"
#include "triangleMesh.h"

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

const float toRadians = 3.14159265f / 180.0f;

static const char* vShader = "./vertex.glsl";
static const char* fShader = "./fragment.glsl";

glfwWindow mainWindow;
std::vector<CShader*> shaderList;
std::vector<triangleMesh*> meshList;


void CreateTriangle()
{
  unsigned int indices[] = { 0, 3, 1,
                             1, 3, 2,
                             2, 3, 0,
                             0, 1, 2 };

  GLfloat vertices[] = { -1.0f, -1.0f, 0.0f,
                          0.0f, -1.0f, 1.0f,
                          1.0f, -1.0f, 0.0f,
                          0.0f,  1.0f, 0.0f};

  //glGenVertexArrays(1, &VAO);
  //glBindVertexArray(VAO);

  //glGenBuffers(1, &VBO);
  //glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  //glEnableVertexAttribArray(0);

  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  //glBindVertexArray(0);

  triangleMesh* obj1 = new triangleMesh();
  obj1->createMesh(vertices, indices, 12, 12);
  meshList.push_back(obj1);

  triangleMesh* obj2 = new triangleMesh();
  obj2->createMesh(vertices, indices, 12, 12);
  meshList.push_back(obj2);
}


void createShaders()
{
  CShader* shader1 = new CShader();
  shader1->createFromFiles(vShader, fShader);
  shaderList.push_back(shader1);
}



int main(int argc, char** argv)
{
  int ret = 0;

  mainWindow = glfwWindow(800, 600);
  if (!mainWindow.initialise())
  {
    CreateTriangle();
    createShaders();

    GLuint uProjection = 0;
    GLuint uModel = 0;

    glm::mat4 proj(glm::perspective(glm::radians(45.0f), (GLfloat)(WIDTH / HEIGHT), 0.1f, 100.0f));


    while (!mainWindow.getShouldClose())
    {
      glfwPollEvents();

      glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //glUseProgram(shader);
      shaderList[0]->useShader();
      uModel = shaderList[0]->getModelLocation();
      uProjection = shaderList[0]->getProjectionLocation();

      glm::mat4 model(1.0f);

      model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
      model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
      glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(proj));
      meshList[0]->renderMesh();

      model = glm::mat4(1.0);
      model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
      model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
      glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
      meshList[1]->renderMesh();

      glUseProgram(0);

      mainWindow.swapBuffers();
    }
  }

  return 0;
}