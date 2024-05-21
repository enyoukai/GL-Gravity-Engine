#include "Mesh.h"

// FIXME: This is a hack to get M_PI to work with MSVC
#include <corecrt_math_defines.h>
// #define _USE_MATH_DEFINES
// #include <cmath>

#include "MathUtils.h"
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_DYNAMIC_DRAW);

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
		// lat 0 is the top pole, lat latitudeCount is one before the bottom pole
		for (int lat = 0; lat < latitudeCount; lat++)
		{
			for (int lon = 0; lon < longitudeCount; lon++)
			{
				double doubleLat = lat;
				double doubleLon = lon;

				if (lat == 0)
				{
					double lowerPhi = (M_PI / 2) - M_PI * ((doubleLat + 1) / (latitudeCount + 1));
					double leftTheta = 2 * M_PI * (doubleLon / longitudeCount);
					double rightTheta = 2 * M_PI * ((doubleLon + 1) / longitudeCount);

					Vec3 topVertex = {0, 0, radius};
					Vec3 v1 = MathUtils::GetSphereVertex(radius, leftTheta, lowerPhi);
					Vec3 v2 = MathUtils::GetSphereVertex(radius, rightTheta, lowerPhi);

					VecUtils::AppendVecToVector(sphereVertices, topVertex);
					VecUtils::AppendVecToVector(sphereVertices, v1);
					VecUtils::AppendVecToVector(sphereVertices, v2);
				}

				else if (lat == latitudeCount - 1)
				{
					double upperPhi = (M_PI / 2) - M_PI * ((doubleLat) / (latitudeCount + 1));
					double leftTheta = 2 * M_PI * (doubleLon / longitudeCount);
					double rightTheta = 2 * M_PI * ((doubleLon + 1) / longitudeCount);

					Vec3 bottomVertex = {0, 0, -radius};
					Vec3 v1 = MathUtils::GetSphereVertex(radius, leftTheta, upperPhi);
					Vec3 v2 = MathUtils::GetSphereVertex(radius, rightTheta, upperPhi);

					VecUtils::AppendVecToVector(sphereVertices, bottomVertex);
					VecUtils::AppendVecToVector(sphereVertices, v1);
					VecUtils::AppendVecToVector(sphereVertices, v2);
				}
				else
				{
					double upperPhi = (M_PI / 2) - M_PI * (doubleLat / (latitudeCount + 1));
					double lowerPhi = (M_PI / 2) - M_PI * ((doubleLat + 1) / (latitudeCount + 1));

					double leftTheta = 2 * M_PI * (doubleLon / longitudeCount);
					double rightTheta = 2 * M_PI * ((doubleLon + 1) / longitudeCount);

					Vec3 v1 = MathUtils::GetSphereVertex(radius, leftTheta, upperPhi);
					Vec3 v2 = MathUtils::GetSphereVertex(radius, rightTheta, upperPhi);
					Vec3 v3 = MathUtils::GetSphereVertex(radius, rightTheta, lowerPhi);

					VecUtils::AppendVecToVector(sphereVertices, v1);
					VecUtils::AppendVecToVector(sphereVertices, v2);
					VecUtils::AppendVecToVector(sphereVertices, v3);

					Vec3 v4 = MathUtils::GetSphereVertex(radius, leftTheta, upperPhi);
					Vec3 v5 = MathUtils::GetSphereVertex(radius, rightTheta, lowerPhi);
					Vec3 v6 = MathUtils::GetSphereVertex(radius, leftTheta, lowerPhi);

					VecUtils::AppendVecToVector(sphereVertices, v4);
					VecUtils::AppendVecToVector(sphereVertices, v5);
					VecUtils::AppendVecToVector(sphereVertices, v6);
				}
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