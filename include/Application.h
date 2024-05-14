#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application(std::string applicationName);
	~Application();
	void run();
	void update();
	void render();

	GLFWwindow *window;

private:
	std::string applicationName;
	unsigned int shaderProgram;
	unsigned int VAO;

	void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	void processInput(GLFWwindow *window);

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "void main()\n"
									   "{\n"
									   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									   "}\n\0";
};