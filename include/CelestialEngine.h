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
private:
	std::vector<CelestialBody> bodies;

public:
	void Simulate(float dt);
	void AddBody(CelestialBody body);
};

namespace CelestialBodyFactory
{
	const double sunMass = 1000;
	const double sunRadius = 10;

	const double earthMass = 10;
	const double earthRadius = 1;

	const double moonMass = 7.342e22;
	const double moonRadius = 1.737e6;

	const double blackHoleMass = 1e31;
	const double blackHoleRadius = 1e5;

	CelestialBody CreateBody(float mass, float radius, Vec3 position, Vec3 velocity);
	CelestialBody CreateSun();
	CelestialBody CreateEarth();

	CelestialBody CreateSun(Vec3 position, Vec3 velocity);
	CelestialBody CreateEarth(Vec3 position, Vec3 velocity);
};