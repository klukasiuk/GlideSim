#include "math.h"

Vec3::Vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vec3 Vec3::operator+(Vec3 v)
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

void Vec3::operator+=(Vec3 v)
{
	x = x + v.x;
	y = y + v.y;
	x = x + v.x;
}

Vec3 Vec3::operator-(Vec3 v)
{
	return Vec3();
}

void Vec3::operator-=(Vec3 v)
{
}

Vec3 Vec3::operator*(float s)
{
	return Vec3();
}

void Vec3::operator*=(float s)
{
}

void clamp(int & val, int min, int max)
{
	if (val < min)
		val = min;

	if (val > max)
		val = max;
}

void clamp(float & val, float min, float max)
{
	if (val < min)
		val = min;

	if (val > max)
		val = max;
}

void clamp(double & val, double min, double max)
{
	if (val < min)
		val = min;

	if (val > max)
		val = max;
}
