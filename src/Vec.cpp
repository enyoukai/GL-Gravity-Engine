#include <cmath>

#include "Vec.h"

double Vec3::Length()
{
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalize()
{
	double length = Length();

	return {x / length, y / length, z / length};
}