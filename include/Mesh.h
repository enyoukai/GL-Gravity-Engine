#pragma once

#include <vector>

class Mesh
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int vertexCount;
	unsigned int indexCount;

public:
	void SetVertices(std::vector<double> &vertices);
	void Draw();
};

namespace MeshFactory
{
	Mesh CreateSphere(float radius, int resolution);
}