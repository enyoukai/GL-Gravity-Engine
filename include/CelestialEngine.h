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
public:
	std::vector<CelestialBody> bodies;

	void Simulate(float dt);
	void AddBody(CelestialBody body);
};

namespace CelestialBodyFactory
{
	const double sunMass = 1.989e30;
	const double sunRadius = 6.9634e8;

	const double earthMass = 5.972e24;
	const double earthRadius = 6.371e6;

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