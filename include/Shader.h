#pragma once

#include <string>

class Shader
{
public:
	Shader(std::string programName, const char *vertexPath, const char *fragmentPath);

	void CompileProgram();
	void Use();

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;

private:
	unsigned int ID;

	std::string vertexCode;
	std::string fragmentCode;

	std::string programName;

	bool LoadShaderFromPath(const char *vertexPath, const char *fragmentPath);

	bool CheckShaderCompilation(unsigned int shader, std::string type);
	bool CheckProgramCompilation(unsigned int program);
};