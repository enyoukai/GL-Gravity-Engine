#pragma once

template <typename T>
class Vec3
{
public:
	T x;
	T y;
	T z;

	T Length();
	Vec3<T> Normalize();

	Vec3 operator+(Vec3 a)
	{
		return {x + a.x, y + a.y, z + a.z};
	}

	Vec3 operator-(Vec3 a)
	{
		return {x - a.x, y - a.y, z - a.z};
	}

	Vec3 operator*(double a)
	{
		return {x * a, y * a, z * a};
	}

	Vec3 operator/(double a)
	{
		return {x / a, y / a, z / a};
	}

	Vec3 &operator+=(Vec3 a)
	{
		x += a.x;
		y += a.y;
		z += a.z;

		return *this;
	}

	Vec3 &operator-=(Vec3 a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;

		return *this;
	}
};

namespace VecUtils
{
	template <typename T>
	T AppendVecToVector(std::vector<T> &vector, Vec3<T> vec);
}