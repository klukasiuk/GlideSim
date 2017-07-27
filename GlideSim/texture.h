#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
private :

	GLuint ID;

public :

	Texture(char * texName);
   ~Texture();

   void bind();
};