#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "error.h"

class Shader
{
private:

	GLuint programID;																	// ID for shading program

	string vertex_shader_path;															// Paths to shader files
	string fragment_shader_path;

public:

	Shader(char * vertex_file_path, char * fragment_file_path);							// Load shaders, compiles them , compiles program and set program ID
	~Shader();

	void use();																			// Bind shader for use

	void reload();

	GLuint getID();

	GLuint getUniform(char * name);
	GLuint getUniform(string & name);

	void Shader::setBool(string &name, bool value);
	void Shader::setInt(string &name, int value);
	void Shader::setFloat(string &name, float value);

	void Shader::setVec2(string &name, glm::vec2 &value);
	void Shader::setVec2(string &name, float x, float y);
	void Shader::setVec3(char * name, glm::vec3 &value);
	void Shader::setVec3(string &name, glm::vec3 &value);
	void Shader::setVec3(char * name, float x, float y, float z);
	void Shader::setVec3(string &name, float x, float y, float z);
	void Shader::setVec4(string &name, glm::vec4 &value);
	void Shader::setVec4(string &name, float x, float y, float z, float w);

	void Shader::setMat2(string &name, glm::mat2 &mat);
	void Shader::setMat3(string &name, glm::mat3 &mat);
	void Shader::setMat4(char * name, glm::mat4 &mat);
	void Shader::setMat4(string &name, glm::mat4 &mat);
};