#include <spdlog/spdlog.h>

#include "CelestialEngine.h"
#include "Physics.h"

void CelestialEngine::Simulate(float dt)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = 0; j < bodies.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			double distance = (bodies[j].position - bodies[i].position).Length();

			double force = Physics::CalculateGravitationalForce(bodies[i].mass, bodies[j].mass, distance);

			Vec3 direction = (bodies[j].position - bodies[i].position).Normalize();

			bodies[i].velocity += direction * (force / bodies[i].mass) * dt;
		}
	}

	for (CelestialBody body : bodies)
	{
		body.position += body.velocity * dt;
		spdlog::debug("Position: ({}, {}, {})", body.position.x, body.position.y, body.position.z);
	}
}

void CelestialEngine::AddBody(CelestialBody body)
{
	bodies.push_back(body);
}

namespace CelestialBodyFactory
{
	CelestialBody CreateBody(float mass, float radius, Vec3 position, Vec3 velocity)
	{
		return {mass, radius, position, velocity};
	}

	CelestialBody CreateSun(Vec3 position, Vec3 velocity)
	{
		return CreateBody(sunMass, sunRadius, position, velocity);
	}

	CelestialBody CreateSun()
	{
		return CreateBody(sunMass, sunRadius, {0, 0, 0}, {0, 0, 0});
	}

	CelestialBody CreateEarth(Vec3 position, Vec3 velocity)
	{
		return CreateBody(earthMass, earthRadius, position, velocity);
	}

	CelestialBody CreateEarth()
	{
		return CreateBody(earthMass, earthRadius, {0, 0, 0}, {0, 0, 0});
	}
}