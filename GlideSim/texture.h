#pragma once

#include <GLFW/glfw3.h>

class Texture
{
private :

	GLuint ID;

public :

	Texture(char * texName);
   ~Texture();

   void bind();

   void keyColor(int r, int g, int b);
};