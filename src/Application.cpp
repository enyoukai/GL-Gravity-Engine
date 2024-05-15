#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

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
	glEnable(GL_DEBUG_OUTPUT);
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
	Shader shader("PlanetShader", "C:\\Users\\enyoukai\\code\\gl-gravitation\\src\\shaders\\planetShader.vert", "C:\\Users\\enyoukai\\code\\gl-gravitation\\src\\shaders\\planetShader.frag");

	shader.CompileProgram();
	shader.Use();

	CelestialBody sun = CelestialBodyFactory::CreateSun();
	CelestialBody earth = CelestialBodyFactory::CreateEarth({1.5e11, 0, 0}, {0, 29784});

	engine.AddBody(sun);
	engine.AddBody(earth);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

void Application::Update()
{
	double dt = glfwGetTime() - previousTime;
	previousTime = glfwGetTime();

	engine.Simulate(dt * 3.154e7);
}

void Application::Render()
{
	processInput(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	CelestialBody earth = engine.bodies[1];

	float SCALE = 500000000000.95966;
	float vertices[9];
	vertices[0] = earth.position.x / SCALE;
	vertices[1] = earth.position.y / SCALE;
	vertices[2] = 0;

	vertices[3] = earth.position.x / SCALE + 0.01;
	vertices[4] = earth.position.y / SCALE;
	vertices[5] = 0;

	vertices[6] = earth.position.x / SCALE;
	vertices[7] = earth.position.y / SCALE + 0.01;
	vertices[8] = 0;

	spdlog::info("Position: ({}, {}, {})", earth.position.x, earth.position.y, earth.position.z);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 3);

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