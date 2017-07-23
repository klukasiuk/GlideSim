#pragma once


struct Vec3
{
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float X, float Y, float Z);

	Vec3 operator +  (Vec3 v);
	void operator += (Vec3 v);

	Vec3 operator -  (Vec3 v);
	void operator -= (Vec3 v);

	Vec3 operator *  (float s);
	void operator *= (float s);

};

void clamp(int & val, int min, int max);
void clamp(float & val, float min, float max);
void clamp(int & val, int min, int max);

float fast_inv_sqrt(float var);