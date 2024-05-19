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

	earthMesh.Init();
	cubeMesh = MeshFactory::CreateCube(0.1);
}

void Application::Update()
{
	dt = glfwGetTime() - previousTime;
	previousTime = glfwGetTime();

	processInput(window);

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

	earthMesh.SetVertices(vertices);
	earthMesh.Draw();

	spdlog::debug("Position: ({}, {}, {})", earth.position.x, earth.position.y, earth.position.z);

	cubeMesh.Draw();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, dt);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}