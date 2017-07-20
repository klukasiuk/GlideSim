#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

class SimpleWindow
{

public :

	// Window variables
	GLFWwindow * window;

	int WindowWidth = 0;
	int WindowHeight = 0;

	void initWindow(int width, int height, char * name);

	void closeWindow();

	bool shouldClose();

	void swapBuffer();

	void initOGL();

};