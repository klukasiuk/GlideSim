#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window
{
private :

	GLFWwindow * window;

	int WindowWidth = 0;
	int WindowHeight = 0;

	std::string WindowName;

public :

	Window(int Width, int Height, char * WindowName);
   ~Window();

   GLFWwindow * getHandle();

   void makeCurrent();


};