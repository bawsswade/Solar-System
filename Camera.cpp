#define GLM_SWIZZLE
#define  GLFW_KEY_RIGHT   262 
#define  GLFW_KEY_LEFT   263 
#define  GLFW_KEY_DOWN   264 
#define  GLFW_KEY_UP   265 
#include "Camera.h"
#include <iostream>

double Camera::X_SCROLL = 0.0;
double Camera::Y_SCROLL = 0.0;

void Camera::Update(float deltaTime)
{
	Gizmos::draw(getProjection() * getView());
}

void Camera::SetPersp(float fov, float aspectRatio, float near, float far)
{
	projectionTransform = perspective(fov, aspectRatio, near, far);
}

// sets viewTrans and recalcs world trans (direction components)
void Camera::SetLookAt(vec3 from, vec3 to, vec3 up)
{
	worldTransform = inverse(lookAt(from, to, up));
}

// sets worldTrans and recvalcs view trans (position component)
void Camera::SetPosition(vec3 position)
{
	worldTransform[3].xyz = position;
}

void Camera::scrollFunc(GLFWwindow *w, double x, double y)
{
	std::cout << y << std::endl;
	X_SCROLL = x;
	Y_SCROLL = y;
}


void Camera::Input(GLFWwindow *window, float speed, float deltaTime)
{
	glfwSetScrollCallback(window, scrollFunc);

	/*if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		worldTransform[3].xyz += -1 * worldTransform[0].xyz * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		worldTransform[3].xyz += worldTransform[0].xyz * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		worldTransform[3].xyz += worldTransform[1].xyz * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		worldTransform[3].xyz -= worldTransform[1].xyz *speed * deltaTime;
	}*/
	if ( Y_SCROLL == -1)
	{
		worldTransform[3].xyz += worldTransform[2].xyz * speed * deltaTime * 100;
		Y_SCROLL = 0;
	}
	if ( Y_SCROLL == 1)
	{
		worldTransform[3].xyz -= worldTransform[2].xyz * speed * deltaTime * 100;
		Y_SCROLL = 0;
	}

	glfwGetCursorPos(window, &currentXCursor, &currentYCursor);
	deltaXCursor = currentXCursor - lastXCursor;
	deltaYCursor = currentYCursor - lastYCursor;
	lastXCursor = currentXCursor;
	lastYCursor = currentYCursor;

	// scrollbar click
	if (glfwGetMouseButton(window, 2))
	{
		if (deltaXCursor > 0)
		{
			worldTransform[3] -= worldTransform[0] * speed * deltaXCursor *  deltaTime;
		}
		if (deltaXCursor < 0)
		{
			worldTransform[3] += worldTransform[0] * speed * -deltaXCursor * deltaTime;
		}
		if (deltaYCursor < 0)
		{
			worldTransform[3] -= worldTransform[1] * speed * -deltaYCursor * deltaTime;
		}
		if (deltaYCursor > 0)
		{
			worldTransform[3] += worldTransform[1] * speed * deltaYCursor * deltaTime;
		}
	}
	

	// right click
	if (glfwGetMouseButton(window, 1))
	{
		if (deltaXCursor > 0)
		{
			//worldTransform = rotate((double)deltaXCursor, vec3(0, 1, 0));
			//worldTransform = rotate(worldTransform, 10, vec3(0, 1, 0));
			//worldTransform = rotateX(glm::vec3(worldTransform[3].xyz), (const double) deltaXCursor);
		}
		if (deltaXCursor < 0)
		{
			//worldTransform[0] += worldTransform[0] * speed * -deltaXCursor * deltaTime;
		}
		if (deltaYCursor < 0)
		{
			//worldTransform[2] -= worldTransform[1] * speed * -deltaYCursor * deltaTime;
		}
		if (deltaYCursor > 0)
		{
			//worldTransform[2] += worldTransform[1] * speed * deltaYCursor * deltaTime;
		}
	}
}