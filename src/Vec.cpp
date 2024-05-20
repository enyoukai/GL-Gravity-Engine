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

namespace VecUtils
{
	void AppendVecToVector(std::vector<double> &vector, Vec3 vec)
	{
		vector.push_back(vec.x);
		vector.push_back(vec.y);
		vector.push_back(vec.z);
	}
}