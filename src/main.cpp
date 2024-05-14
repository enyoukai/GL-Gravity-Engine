#include "Application.h"

#include <iostream>

// settings

int main()
{
	Application application("Enyoukai's Gravity Engine");

	while (!glfwWindowShouldClose(application.window))
	{
		application.render();
	}

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------