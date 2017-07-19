#pragma once

#include <GLM/glm.hpp>

namespace color
{
	glm::vec3 RGB(int r, int g, int b);
	glm::vec4 RGBA(int r, int g, int b, int a);

	extern glm::vec3 red;
	extern glm::vec3 blue;
	extern glm::vec3 green;
	extern glm::vec3 black;
	extern glm::vec3 white;
	extern glm::vec3 magenta;
	extern glm::vec3 yellow;
	extern glm::vec3 cyan;
}
