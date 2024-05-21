#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "CelestialEngine.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

class Application
{
public:
	Application(std::string applicationName);
	void Run();
	void Load();
	void Start();
	void Update();
	void Render();

	GLFWwindow *window;

private:
	std::string applicationName;

	CelestialEngine engine;

	double previousTime = 0.0;
	double dt = 0;

	void HandleCursorMovement(GLFWwindow *window, double xpos, double ypos);
	void HandleFramebufferResizing(GLFWwindow *window, int width, int height);
	void ProcessInput(GLFWwindow *window);

	const unsigned int scrWidth = 1920;
	const unsigned int scrHeight = 1080;

	float lastMouseX = scrWidth / 2.0f;
	float lastMouseY = scrHeight / 2.0f;

	// state for first time glfwSetCursorPosCallback is called
	bool firstMouse = true;

	Mesh earthMesh;
	Mesh cubeMesh;
	Mesh sphereMesh;

	// not ideal but will do for now
	Camera camera = Camera(1920, 1080);

	Shader planetShader;
};