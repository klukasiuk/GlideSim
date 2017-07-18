#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "error.h"

class Shader
{
private :

	GLuint programID;																	// ID for shading program

public :

	Shader(const char * vertex_file_path, const char * fragment_file_path);				// Load shaders, compiles them , compiles program and set program ID
   ~Shader();

	void use();																			// Bind shader for use

	GLuint getID();
};