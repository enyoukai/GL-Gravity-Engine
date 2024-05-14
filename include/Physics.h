#pragma once

namespace Physics
{
	const double GRAVITATIONAL_CONSTANT = 6.67430e-11;

	double CalculateGravitationalForce(double mass1, double mass2, double distance);
}