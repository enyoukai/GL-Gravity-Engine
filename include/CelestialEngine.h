#pragma once

#include <vector>

#include "Vec.h"

typedef struct CelestialBody
{
	float mass;
	float radius;

	Vec3 position;
	Vec3 velocity;
} CelestialBody;

class CelestialEngine
{
	std::vector<CelestialBody> bodies;

	void Simulate(float dt);
	void AddBody(CelestialBody body);
};

class CelestialBodyFactory
{
	static CelestialBody CreateBody(float mass, float radius, float x, float y, float z, float vx, float vy, float vz);

	static CelestialBody CreateSun();
	static CelestialBody CreateEarth();
	static CelestialBody CreateMoon();
	static CelestialBody CreateBlackHole();
};