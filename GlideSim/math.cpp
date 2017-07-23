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

// Fast inverse sqrt from Quake source code
float fast_inv_sqrt(float var)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = var * 0.5F;
	y = var;
	i = *(long *)&y;							// evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);					// what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));		// 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}