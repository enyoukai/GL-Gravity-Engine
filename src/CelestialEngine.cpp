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

			bodies[i].velocity += direction * force / bodies[i].mass * dt;
		}
	}

	for (CelestialBody body : bodies)
	{
		body.position += body.velocity * dt;
	}
}