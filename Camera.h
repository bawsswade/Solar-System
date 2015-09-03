#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <aie\Gizmos.h>
#include <GLFW\glfw3.h>
//#include <GLFW\glfw3native.h>

#include <iostream>

using namespace glm;

class Camera
{
	// world(model) transform
	mat4 worldTransform;
	// 
	// projection
	mat4 projectionTransform;
	vec3 center = {0, 0, 0};

	
	static void scrollFunc(GLFWwindow* w, double x, double y);
	static double X_SCROLL, Y_SCROLL;

	double lastXCursor = 0, lastYCursor = 0, currentXCursor = 0, currentYCursor = 0;
	double deltaXCursor = 0, deltaYCursor = 0;

	bool controlled = false;

public:
	
	void Update(float deltaTime);
	void SetPersp(float fov, float aspectRatio, float near, float far);

	// sets viewTrans and recalcs world trans (direction components)
	void SetLookAt(vec3 from, vec3 to, vec3 up);

	// sets worldTrans and recvalcs view trans (position component)
	void SetPosition(vec3 position);

	mat4 getWorldTransform() { return worldTransform; }
	mat4 getView() { return inverse( worldTransform); }
	mat4 getProjection() { return projectionTransform; }

	void Input(GLFWwindow *window, float speed, float deltaTime);
};