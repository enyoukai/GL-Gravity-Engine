#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application(std::string applicationName);
	void Run();
	void Load();
	void Update();
	void Render();

	GLFWwindow *window;

private:
	std::string applicationName;

	void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	void processInput(GLFWwindow *window);

	const unsigned int scrWidth = 1920;
	const unsigned int scrHeight = 1080;
};