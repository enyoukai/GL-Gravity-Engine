#include "Mesh.h"

// FIXME: This is a hack to get M_PI to work with MSVC
#include <corecrt_math_defines.h>
// #define _USE_MATH_DEFINES
// #include <cmath>

#include "Math.h"
#include "Vec.h"

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

		// we treat sphere vertices where x and y lie on the 2d plane and z is the height
		for (int lat = 0; lat < latitudeCount; lat++)
		{
			for (int lon = 0; lon < longitudeCount; lon++)
			{
				// double theta = 2 * M_PI * (lon / longitudeCount);
				// double phi = M_PI * (lat / (latitudeCount + 1));

				if (lat == 0)
				{
					double lowerPhi = M_PI * ((lat + 1) / (latitudeCount + 1));
					double leftTheta = 2 * M_PI * (lon / longitudeCount);
					double rightTheta = 2 * M_PI * ((lon + 1) / longitudeCount);

					Vec3 v1 = Math::GetSphereVertex(radius, leftTheta, lowerPhi);
					Vec3 v2 = Math::GetSphereVertex(radius, rightTheta, lowerPhi);

					sphereVertices.push_back(radius * cos(lowerPhi) * cos(leftTheta));
					sphereVertices.push_back(radius * cos(lowerPhi) * sin(leftTheta));
					sphereVertices.push_back(radius * sin(lowerPhi));

					sphereVertices.push_back(radius * cos(lowerPhi) * cos(rightTheta));
					sphereVertices.push_back(radius * cos(lowerPhi) * sin(rightTheta));
					sphereVertices.push_back(radius * sin(lowerPhi));
				}

				else if (lat == latitudeCount - 1)
				{
					double upperPhi = M_PI * ((lat - 1) / (latitudeCount + 1));
					double leftTheta = 2 * M_PI * (lon / longitudeCount);
					double rightTheta = 2 * M_PI * ((lon + 1) / longitudeCount);

					sphereVertices.push_back(radius * cos(upperPhi) * cos(leftTheta));
					sphereVertices.push_back(radius * cos(upperPhi) * sin(leftTheta));
					sphereVertices.push_back(radius * sin(upperPhi));

					sphereVertices.push_back(radius * cos(upperPhi) * cos(rightTheta));
					sphereVertices.push_back(radius * cos(upperPhi) * sin(rightTheta));
					sphereVertices.push_back(radius * sin(upperPhi));

					sphereVertices.push_back(0);
					sphereVertices.push_back(0);
					sphereVertices.push_back(-radius);
				}
				else
				{
					double upperPhi = M_PI * (lat / (latitudeCount + 1));
					double lowerPhi = M_PI * ((lat + 1) / (latitudeCount + 1));

					double leftTheta = 2 * M_PI * (lon / longitudeCount);
					double rightTheta = 2 * M_PI * ((lon + 1) / longitudeCount);

					sphereVertices.push_back(radius * cos(upperPhi) * cos(leftTheta));
					sphereVertices.push_back(radius * cos(upperPhi) * sin(leftTheta));
					sphereVertices.push_back(radius * sin(upperPhi));

					sphereVertices.push_back(radius * cos(lowerPhi) * cos(leftTheta));
					sphereVertices.push_back(radius * cos(lowerPhi) * sin(leftTheta));
					sphereVertices.push_back(radius * sin(lowerPhi));

					sphereVertices.push_back(radius * cos(lowerPhi) * cos(rightTheta));
					sphereVertices.push_back(radius * cos(lowerPhi) * sin(rightTheta));
					sphereVertices.push_back(radius * sin(lowerPhi));

					sphereVertices.push_back(radius * cos(upperPhi) * cos(rightTheta));
					sphereVertices.push_back(radius * cos(upperPhi) * sin(rightTheta));
					sphereVertices.push_back(radius * sin(upperPhi));

					sphereVertices.push_back(radius * cos(lowerPhi) * cos(rightTheta));
					sphereVertices.push_back(radius * cos(lowerPhi) * sin(rightTheta));
					sphereVertices.push_back(radius * sin(lowerPhi));

					sphereVertices.push_back(radius * cos(upperPhi) * cos(leftTheta));
					sphereVertices.push_back(radius * cos(upperPhi) * sin(leftTheta));
					sphereVertices.push_back(radius * sin(upperPhi));
				}
			}
			sphereMesh.SetVertices(sphereVertices);

			return sphereMesh;
		}
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