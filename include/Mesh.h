#pragma once

#include <vector>

class Mesh
{
	unsigned int VAO;
	unsigned int VBO;

	unsigned int vertexCount;

public:
	void Init();
	void SetVertices(std::vector<double> &vertices);
	void Draw();
};

namespace MeshFactory
{
	Mesh CreateSphere(double radius, int latitudeCount, int longitudeCount);
	Mesh CreateCube(double sideLength);
}