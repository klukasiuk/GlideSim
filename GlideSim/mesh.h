#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"


using std::vector;


class Mesh
{
private :

	vector<unsigned short> indices;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	vector<glm::vec3> colors;

	GLuint vertexArrayID;

	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalBufferID;
	GLuint colorBufferID;

public :

	Mesh(vector<unsigned short> indices, vector<glm::vec3> vertices, vector<glm::vec2> uvs, vector<glm::vec3> normals, vector<glm::vec3> colors);
   ~Mesh();

	void draw(Shader * shader);
};