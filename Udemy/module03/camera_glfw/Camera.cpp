#include "Camera.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	currentTheta = 0;
	currentPhi = 0;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		fprintf(stderr, "deal with right key press\n");
		glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		position = glm::vec3(glm::vec4(position, 1.0f) * mat);

	}

	if (keys[GLFW_KEY_LEFT])
	{
		fprintf(stderr, "deal with left key press\n");
		glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		position = glm::vec3(glm::vec4(position, 1.0f) * mat);
	}

	if (keys[GLFW_KEY_UP])
	{
		glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		position = glm::vec3(glm::vec4(position, 1.0f) * mat);
	}

	if (keys[GLFW_KEY_DOWN])
	{
		glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		position = glm::vec3(glm::vec4(position, 1.0f) * mat);
	}

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
