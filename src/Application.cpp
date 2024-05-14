#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <string>

#include "Application.h"

Application::Application(std::string applicationName)
{
	spdlog::info("Creating application {}", applicationName);
	this->applicationName = applicationName;
}

void Application::Run()
{
	Load();

	Start();

	while (!glfwWindowShouldClose(window))
	{
		Update();
		Render();
	}

	glfwTerminate();
}

void Application::Load()
{
	spdlog::info("Loading application {}", applicationName);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(scrWidth, scrHeight, applicationName.c_str(), NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	previousTime = glfwGetTime();

	spdlog::info("Finished loading application");
}

void Application::Start()
{
	CelestialBody sun = CelestialBodyFactory::CreateSun();
	CelestialBody earth = CelestialBodyFactory::CreateEarth({100, 0, 100}, {10, 0, 10});

	engine.AddBody(sun);
	engine.AddBody(earth);
}

void Application::Update()
{
	double dt = glfwGetTime() - previousTime;

	engine.Simulate(dt);
}

void Application::Render()
{
	// input
	// -----
	processInput(window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}