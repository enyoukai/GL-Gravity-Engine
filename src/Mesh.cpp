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
	Mesh CreateSphere(double radius, int resolution)
	{
		Mesh sphereMesh;
		sphereMesh.Init();

		std::vector<double> sphereVertices;

		for (int i = 0; i <= resolution; i++)
		{
			double theta = i * M_PI / resolution;
			double sinTheta = sin(theta);
			double cosTheta = cos(theta);

			for (int j = 0; j <= resolution; j++)
			{
				double phi = j * 2 * M_PI / resolution;
				double sinPhi = sin(phi);
				double cosPhi = cos(phi);

				double x = cosPhi * sinTheta;
				double y = cosTheta;
				double z = sinPhi * sinTheta;

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
			// Front face
			-0.5, -0.5, 0.5, // Bottom-left
			0.5, -0.5, 0.5,	 // Bottom-right
			0.5, 0.5, 0.5,	 // Top-right
			-0.5, 0.5, 0.5,	 // Top-left
			// Back face
			-0.5, -0.5, -0.5, // Bottom-left
			0.5, -0.5, -0.5,  // Bottom-right
			0.5, 0.5, -0.5,	  // Top-right
			-0.5, 0.5, -0.5,  // Top-left
			// Left face
			-0.5, -0.5, -0.5, // Bottom-front
			-0.5, -0.5, 0.5,  // Bottom-back
			-0.5, 0.5, 0.5,	  // Top-back
			-0.5, 0.5, -0.5,  // Top-front
			// Right face
			0.5, -0.5, -0.5, // Bottom-front
			0.5, -0.5, 0.5,	 // Bottom-back
			0.5, 0.5, 0.5,	 // Top-back
			0.5, 0.5, -0.5,	 // Top-front
			// Top face
			-0.5, 0.5, 0.5,	 // Front-left
			0.5, 0.5, 0.5,	 // Front-right
			0.5, 0.5, -0.5,	 // Back-right
			-0.5, 0.5, -0.5, // Back-left
			// Bottom face
			-0.5, -0.5, 0.5, // Front-left
			0.5, -0.5, 0.5,	 // Front-right
			0.5, -0.5, -0.5, // Back-right
			-0.5, -0.5, -0.5 // Back-left
		};

		for (int i = 0; i < cubeVertices.size(); i++)
		{
			cubeVertices[i] *= sideLength;
		}

		cubeMesh.SetVertices(cubeVertices);

		return cubeMesh;
	}
}