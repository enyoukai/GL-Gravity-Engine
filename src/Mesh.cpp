#include "Mesh.h"

// FIXME: This is a hack to get M_PI to work with MSVC
#include <corecrt_math_defines.h>
// #define _USE_MATH_DEFINES
// #include <cmath>

#include <glad/glad.h>

void Mesh::SetVertices(std::vector<double> &vertices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Don't hardcode the format for bufferData and vertexAttribPointer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void *)0);
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
	Mesh CreateSphere(float radius, int resolution)
	{
		Mesh sphereMesh;
		std::vector<double> vertices;

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

				vertices.push_back(radius * x);
				vertices.push_back(radius * y);
				vertices.push_back(radius * z);
			}
		}

		sphereMesh.SetVertices(vertices);

		return sphereMesh;
	}
}