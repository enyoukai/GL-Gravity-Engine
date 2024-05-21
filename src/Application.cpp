#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Application.h"
#include "Shader.h"

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

	glfwSetWindowUserPointer(window, this);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback([](GLenum source,
							  GLenum type,
							  GLuint,
							  GLenum severity,
							  GLsizei,
							  const GLchar *message,
							  const void *)
						   {
	if (type == GL_DEBUG_TYPE_ERROR)
	{
		spdlog::error("GL CALLBACK: type = {}, severity = error, message = {}\n", type, message);
	} },
						   nullptr);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfw callback can't accept function signature of a class member function so we use a lambda
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos)
							 {
		Application *app;

		if (!(app = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window))))
			return;

		app->HandleCursorMovement(window, xpos, ypos); });

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
								   {
		Application *app;

		if (!(app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window)))) return;

		app->HandleFramebufferResizing(window, width, height); });

	previousTime = glfwGetTime();

	spdlog::info("Finished loading application");
}

void Application::Start()
{
	planetShader.Init("PlanetShader", "C:\\Users\\enyoukai\\code\\gl-gravitation\\src\\shaders\\planetShader.vert", "C:\\Users\\enyoukai\\code\\gl-gravitation\\src\\shaders\\planetShader.frag");

	planetShader.Use();

	CelestialBody sun = CelestialBodyFactory::CreateSun();
	CelestialBody earth = CelestialBodyFactory::CreateEarth({1.5e11, 0, 0}, {0, 29784});

	engine.AddBody(sun);
	engine.AddBody(earth);

	// earthMesh.Init();
	cubeMesh = MeshFactory::CreateCube(0.1);
	sphereMesh = MeshFactory::CreateSphere(1, 50, 50);
}

void Application::Update()
{
	dt = glfwGetTime() - previousTime;
	previousTime = glfwGetTime();

	ProcessInput(window);

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 projectionMatrix = camera.GetProjectionMatrix();

	planetShader.SetMat4("view", viewMatrix);
	planetShader.SetMat4("projection", projectionMatrix);

	engine.Simulate(dt * 3.154e7);
}

void Application::Render()
{

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CelestialBody earth = engine.bodies[1];

	double SCALE = 500000000000.95966;
	std::vector<double> vertices(9);
	vertices[0] = earth.position.x / SCALE;
	vertices[1] = earth.position.y / SCALE;
	vertices[2] = 0;

	vertices[3] = earth.position.x / SCALE + 0.01;
	vertices[4] = earth.position.y / SCALE;
	vertices[5] = 0;

	vertices[6] = earth.position.x / SCALE;
	vertices[7] = earth.position.y / SCALE + 0.01;
	vertices[8] = 0;

	// earthMesh.SetVertices(vertices);
	// earthMesh.Draw();

	sphereMesh.Draw();

	spdlog::debug("Position: ({}, {}, {})", earth.position.x, earth.position.y, earth.position.z);

	cubeMesh.Draw();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera Keyboard
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::LEFT, dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::RIGHT, dt);

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Application::HandleFramebufferResizing(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::HandleCursorMovement(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos;

	lastMouseX = xpos;
	lastMouseY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}