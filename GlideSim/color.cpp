#include "color.h"

glm::vec3 color::RGB(int r, int g, int b)
{
	float R = (float)r / 255;
	float G = (float)g / 255;
	float B = (float)b / 255;

	return glm::vec3(R,G,B);
}

glm::vec4 color::RGBA(int r, int g, int b, int a)
{
	float R = (float)r / 255;
	float G = (float)g / 255;
	float B = (float)b / 255;
	float A = (float)a / 255;

	return glm::vec4(R, G, B, A);
}

namespace color
{
	glm::vec3 red		(1.0f, 0.0f, 00.0f);
	glm::vec3 green		(0.0f, 1.0f, 0.0f);
	glm::vec3 blue		(0.0f, 0.0f, 1.0f);
	glm::vec3 black		(0.0f, 0.0f, 0.0f);
	glm::vec3 white		(1.0f, 1.0f, 1.0f);
	glm::vec3 magenta	(1.0f, 0.0f, 1.0f);
	glm::vec3 yellow	(1.0f, 1.0f, 0.0f);
	glm::vec3 cyan		(0.0f, 1.0f, 1.0f);
}