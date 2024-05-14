#include "Physics.h"

namespace Physics
{
	double CalculateGravitationalForce(double mass1, double mass2, double distance)
	{
		return GRAVITATIONAL_CONSTANT * mass1 * mass2 / (distance * distance);
	}
}