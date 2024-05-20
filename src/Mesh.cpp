#include "Mesh.h"

// FIXME: This is a hack to get M_PI to work with MSVC
#include <corecrt_math_defines.h>
// #define _USE_MATH_DEFINES
// #include <cmath>

#include <glad/glad.h>

void Mesh::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Mesh::SetVertices(std::vector<double> &vertices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Don't hardcode the format for bufferData and vertexAttribPointer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void *)0);

	vertexCount = vertices.size() / 3;

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

namespace MeshFactory
{
	Mesh CreateSphere(double radius, int latitudeCount, int longitudeCount)
	{
		Mesh sphereMesh;
		sphereMesh.Init();

		std::vector<double> sphereVertices;

		for (int lat = 0; lat <= latitudeCount; ++lat)
		{
			float theta = lat * M_PI / latitudeCount;
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);

			for (int lon = 0; lon <= longitudeCount; ++lon)
			{
				float phi = lon * 2 * M_PI / longitudeCount;
				float sinPhi = sin(phi);
				float cosPhi = cos(phi);

				float x = cosPhi * sinTheta;
				float y = cosTheta;
				float z = sinPhi * sinTheta;

				sphereVertices.push_back(radius * x);
				sphereVertices.push_back(radius * y);
				sphereVertices.push_back(radius * z);
			}
		}

		sphereMesh.SetVertices(sphereVertices);

		return sphereMesh;
	}

	Mesh CreateCube(double sideLength)
	{
		Mesh cubeMesh;

		cubeMesh.Init();

		std::vector<double> cubeVertices = {
			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, 0.5, -0.5,
			0.5, 0.5, -0.5,
			-0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,

			-0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			0.5, 0.5, 0.5,
			0.5, 0.5, 0.5,
			-0.5, 0.5, 0.5,
			-0.5, -0.5, 0.5,

			-0.5, 0.5, 0.5,
			-0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,

			0.5, 0.5, 0.5,
			0.5, 0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, 0.5,
			0.5, 0.5, 0.5,

			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			-0.5, -0.5, 0.5,
			-0.5, -0.5, -0.5,

			-0.5, 0.5, -0.5,
			0.5, 0.5, -0.5,
			0.5, 0.5, 0.5,
			0.5, 0.5, 0.5,
			-0.5, 0.5, 0.5,
			-0.5, 0.5, -0.5};

		for (int i = 0; i < cubeVertices.size(); i++)
		{
			cubeVertices[i] *= sideLength;
		}

		cubeMesh.SetVertices(cubeVertices);

		return cubeMesh;
	}
}