#pragma once
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>

class Application
{
	GLFWwindow *window;
	float deltaTime;
	float lastTime;
	float currentTime;

public:

	int init(int w, int h, const char* title);
	void step();
	void term();
	void draw();

	virtual int  onInit();
	virtual void onStep();
	virtual void onTerm();
	virtual void onDraw();

};