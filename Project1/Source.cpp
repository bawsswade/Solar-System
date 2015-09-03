#include <gl_core_4_4.h>

#include <math.h>
#include <iostream>
#include "planet.h"
#include "Camera.h"

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1600, 900, "This is a window", NULL, NULL);

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create();

	Camera c;
	c.SetLookAt(vec3(10, 15, 10), vec3(0), vec3(0, 1, 0));
	c.SetPersp(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	c.SetPosition(vec3(10, 15, 10));

	

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	float current = 0;
	float last = 0;
	float deltaTime = 0;

	Planet *sun = new Planet(vec3(0, 0, 0), 1.5f, vec4(1.0f, .6f, .1f, .1f));
	Planet *earth = new Planet(vec3(0, 0, 0), .4f, vec4(.5f, .5f, 1.0f, .1f));
	Planet *moon = new Planet(vec3(0, 0, 0), .1f, vec4(.8f, .8f, 0.8f, .1f));

	while (!glfwWindowShouldClose(window) && glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		current = glfwGetTime();
		deltaTime = current - last;
		last = current;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));

		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		

		// draw grid
		for (int i = 0; i < 21; ++i) {
			Gizmos::addLine(vec3(-10 + i, 0, 10),
				vec3(-10 + i, 0, -10),
				i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i),
				vec3(-10, 0, -10 + i),
				i == 10 ? white : black);
		}

		// praise the SUN!
		
		sun->Update(current);
		sun->Draw();

		/*Planet *mercury = new Planet(vec3(0, 0, 5), .2f, vec4(.8f, .8f, .8f, .1f));
		mercury->SetTranslate(vec3(3,0,0));
		mercury->Update(current);
		mercury->Draw();
		
		Planet *venus = new Planet(vec3(00, 0, 0), .4f, vec4(1.0f, .8f, .25f, .1f));
		venus->SetTranslate(vec3(4, 0, 0));
		venus->Update(current);
		venus->Draw();*/
		
		
		earth->SetParent(sun);
		earth->SetTranslate(vec3(5.5, 0, 0));
		earth->SetRotation(vec3(5 * cos(current), 0, 5 * sin(current)));
		earth->Update(current);
		earth->Draw();
		
		
		moon->SetTranslate(vec3(.5f, 0, 0));
		moon->SetRotation(vec3(1.0f * cos(current), 0, 1.0f * sin(current)));
		moon->SetParent(earth);
		moon->Update(current);
		moon->Draw();

		/*Planet *mars = new Planet(vec3(0, 0, 0), .3f, vec4(1.0f, .2f, .2f, .1f));
		mars->SetTranslate(vec3(7, 0, 0));
		mars->Update(current);
		mars->Draw();
		
		Planet *jupiter = new Planet(vec3(0, 0, 0), .7f, vec4(.7f, .6f, .5f, .1f));
		jupiter->SetTranslate(vec3(9, 0, 0));
		jupiter->Update(current);
		jupiter->Draw();
		
		Planet *saturn = new Planet(vec3(0, 0, 0), .4f, vec4(.65f, .6f, .5f, .1f));
		saturn->SetTranslate(vec3(10.5, 0, 0));
		saturn->Update(current);
		saturn->Draw();
		
		Planet *uranus = new Planet(vec3(0, 0, 0), .4f, vec4(.5f, .5f, .6f, .1f));
		uranus->SetTranslate(vec3(12, 0, 0));
		uranus->Update(current);
		uranus->Draw();
		
		Planet *neptune = new Planet(vec3(0, 0, 0), .4f, vec4(.2f, .2f, 1.0f, .1f));
		neptune->SetTranslate(vec3(13.5, 0, 0));
		neptune->Update(current);
		neptune->Draw();*/

		/*mat4 *tmat	 = new mat4(deltaTime);
		mat4 t = glm::rotate(current, glm::vec3(0, 1, .2));*/

		/*Gizmos::addSphere(vec3(5 * cos(last), 0, 5 * sin(last)), .25f, 20, 20, vec4(.25f, 1, .25f, 1));
		Gizmos::addSphere(vec3(10 * cos(last -10), 0, 10 * sin(last-10)), .5f, 20, 20, vec4(1, 1, .25f, 1));
		Gizmos::addSphere(vec3(9 * cos(last-25), 0, 9 * sin(last-25)), .15f, 20, 20, vec4(.25f, 1, 1.0f, 1));*/

		c.Input(window, 1.0f, deltaTime);
		c.Update(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();

	glfwTerminate();
	return 0;
}