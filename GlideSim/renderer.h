#pragma once

#include <vector>

#include "camera.h"
#include "shader.h"
#include "material.h"
#include "light.h"
#include "model.h"
#include "height_map.h"


using std::vector;


class Renderer
{
private :

	PointLight       pointLight;
	DirectionalLight directionalLight;

	vector<Material> materials_vec;

	Model * plane;

	HeightMap * map;

	int Texture;

	Shader * object_shader;
	Shader * light_cube_shader;
	Shader * terrain_shader;

	Material plane_mat;

public :

	void init();

	void release();

	void draw();

	void update();
};