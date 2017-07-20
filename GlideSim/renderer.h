#pragma once

#include "camera.h"
#include "shader.h"

class Renderer
{
private :

	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint uvbuffer;

	GLuint MatrixID;
	glm::mat4 mvp;

	GLuint TextureID;
	GLuint Texture;

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;

	Shader * myShader;

public :

	Camera cam;

	void init();

	void release();

	void draw();

	void update();
};