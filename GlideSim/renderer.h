#pragma once

#include <vector>

#include "camera.h"
#include "shader.h"
#include "material.h"
#include "light.h"
#include "model.h"


using std::vector;


class Renderer
{
private :

	PointLight       pointLight;
	DirectionalLight directionalLight;

	vector<Material> materials_vec;

	Model * plane;

	int Texture;

	Shader * myShader;

public :

	Camera cam;

	void init();

	void release();

	void draw();

	void update();
};