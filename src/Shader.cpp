#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Shader.h"

void Shader::Init(std::string programName, const char *vertexPath, const char *fragmentPath)
{
	if (!LoadShaderFromPath(vertexPath, fragmentPath))
	{
		spdlog::error("Failed to load shader from path");
		return;
	}

	this->programName = programName;
	CompileProgram();
}

void Shader::CompileProgram()
{
	unsigned int vertexShader, fragmentShader;

	const char *vShaderCStr = vertexCode.c_str();
	const char *fShaderCStr = fragmentCode.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCStr, NULL);
#FIXME GL_CALLBACK triggering here
	glCompileShader(vertexShader);

	if (!CheckShaderCompilation(vertexShader, "VERTEX"))
		return;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCStr, NULL);
	glCompileShader(fragmentShader);

	if (!CheckShaderCompilation(fragmentShader, "FRAGMENT"))
		return;

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	if (!CheckProgramCompilation(ID))
		return;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

bool Shader::LoadShaderFromPath(const char *vertexPath, const char *fragmentPath)
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		spdlog::error("Failed loading shader from path");

		return false;
	}

	return true;
}

bool Shader::CheckShaderCompilation(unsigned int shader, std::string type)
{
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		spdlog::error("ERROR::{}::SHADER::COMPILATION_FAILED\n{}", type, infoLog);

		return false;
	}

	return true;
}

bool Shader::CheckProgramCompilation(unsigned int program)
{
	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		spdlog::error("ERROR::{}::PROGRAM::COMPILATION_FAILED\n{}", programName, infoLog);

		return false;
	}

	return true;
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetMat4(const std::string &name, glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}