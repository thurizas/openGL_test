#include <cstdio>
#include <cstring>

#include <vector>
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "line.h"
#include "cone.h"


void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLint       bufferWidth;
GLint       bufferHeight;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;




int main(int argc, char** argv)
{  
  int ret = 0;
  
  // initialize glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create main window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "drawing lines", NULL, NULL);
  if (window != NULL)
  {
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(window);          // make the current context active
    glewExperimental = GL_TRUE;                  // allow glew experimental features

    GLenum error = glewInit();
    if (GLEW_OK == error)
    {
      glEnable(GL_DEPTH_TEST);
      glViewport(0, 0, bufferWidth, bufferHeight);


      camera theCamera;
      theCamera.pos(glm::vec3(3.0f, 3.0f, 3.0f));

      // initialize scene here here
      line line1(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0));        // x-axis
      line1.setColor(glm::vec3(1, 0, 0));

      cone cone1(5, 36, 1.0f, 1 / sqrt3);
      cone1.color(glm::vec3(1, 0, 0));
      glm::mat4 model1 = glm::scale(glm::mat4(1.0), glm::vec3{ 0.15, 0.05, 0.05 });
      model1 = glm::rotate(model1, -90 * DEG2RAD, glm::vec3(0, 0, 1));
      model1 = glm::translate(model1, glm::vec3{ 0, 6.0, 0 });

      line line2(glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));        // y-axis
      line2.setColor(glm::vec3(0, 1, 0));

      cone cone2(5,36,1.0f, 1/sqrt3);
      cone2.color(glm::vec3(0, 1, 0));
      glm::mat4 model2 = glm::scale(glm::mat4(1.0), glm::vec3{ 0.05, 0.15,0.05 });
      model2 = glm::translate(model2, glm::vec3{ 0, 6.0, 0 });

      line line3(glm::vec3(0, 0, -1), glm::vec3(0, 0, 1));        // z axis
      line3.setColor(glm::vec3(0, 0, 1));

      cone cone3(5, 36, 1.0f, 1 / sqrt3);
      cone3.color(glm::vec3(0, 0, 1));
      glm::mat4 model3 = glm::scale(glm::mat4(1.0), glm::vec3{ 0.05, 0.05, 0.15 });
      model3 = glm::rotate(model3, 90 * DEG2RAD, glm::vec3(1, 0, 0));
      model3 = glm::translate(model3, glm::vec3{ 0, 6.0, 0 });


      glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

      float angle = 0.0f;
      float rotationalSpeed = 40.0f;


      float w = SCR_WIDTH;
      float h = SCR_HEIGHT;
      // render loop
      while (!glfwWindowShouldClose(window))
      {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        // input
        // -----
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float angle = deltaTime * rotationalSpeed;

        // update camera position (rotating)
        theCamera.pos(glm::vec3(3.0f * cos(glm::radians(angle)), 3.0f, 3.0f * sin(glm::radians(angle))));
        glm::mat4 view = glm::lookAt(theCamera.pos(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        line1.setMVP(projection * view);
        line2.setMVP(projection * view);
        line3.setMVP(projection * view);
        cone1.mvp(projection * view * model1);
        cone2.mvp(projection * view * model2);
        cone3.mvp(projection * view * model3);

        line1.draw();
        line2.draw();
        line3.draw();
        cone1.draw();
        cone2.draw();
        cone3.draw();

        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
      }

      glfwDestroyWindow(window);
      glfwTerminate();
      ret = 0;
    }
    else
    {
      std::cerr << "failed to initialize GLEW, error: " << glewGetErrorString(error) << std::endl;
      glfwDestroyWindow(window);
      glfwTerminate();
      ret = 1;
    }
  }
  else
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    ret = -1;
  }

  return ret;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}