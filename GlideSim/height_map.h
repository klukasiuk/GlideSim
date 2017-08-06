#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "shader.h"


using std::vector;
using glm::vec3;


struct Chunk
{
	GLuint vao;
	GLuint vbo;
	GLuint cbo;
	GLuint ebo;

	int indices;

	vec3 position;
};


class HeightMap
{
private :

	float chunk_size;

	int segments;

	float map_amplitude;

	vector<Chunk> chunks;

	void create_chunk(vec3 pos);

public :

	HeightMap();

	void update();

	void render(Shader * shader);
};