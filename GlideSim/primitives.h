#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "core.h"

void render_cube( glm::vec3 position, float scale, Shader * shader);