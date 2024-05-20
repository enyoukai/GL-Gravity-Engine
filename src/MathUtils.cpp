#include "MathUtils.h"

namespace MathUtils
{
	Vec3 GetSphereVertex(double radius, double theta, double phi)
	{
		double x = radius * cos(phi) * cos(theta);
		double y = radius * cos(phi) * sin(theta);
		double z = radius * sin(phi);

		return {x, y, z};
	}
}