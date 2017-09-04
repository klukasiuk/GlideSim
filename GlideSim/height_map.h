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
	GLuint ebo;

	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint color_buffer;

	int indices;

	vec3 position;

	vector<float> border_top;
	vector<float> border_down;
	vector<float> border_left;
	vector<float> border_right;
};


class HeightMap
{
private :

	float chunk_size;

	int segments;

	float map_amplitude;

	vector<Chunk> chunks;


	vector<int> find_neighbours(vec3 chunk_pos);

	void create_chunk(vec3 pos);

	bool check_if_chunk_exist(vec3 pos);

public :


	HeightMap();

	void update();

	void render(Shader * shader);
};