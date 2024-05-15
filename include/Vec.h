#pragma once

class Vec3
{
public:
	double x;
	double y;
	double z;

	double Length();
	Vec3 Normalize();

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
