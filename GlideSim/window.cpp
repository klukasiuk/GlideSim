#include "window.h"

#include <stdlib.h>
#include <stdio.h>

void basic_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void basic_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Window::Window(int Width, int Height, char * Name)
{
	WindowWidth = Width;
	WindowHeight = Height;

	WindowName = Name;

	glfwSetErrorCallback(basic_error_callback);

	int isInit;

	isInit = glfwInit();

	if (isInit == GLFW_FALSE)
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WindowWidth, WindowHeight, Name, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, basic_key_callback);

	glfwMakeContextCurrent(window);
}

Window::~Window()
{
}

GLFWwindow * Window::getHandle()
{
	return window;
}

void Window::makeCurrent()
{
	glfwMakeContextCurrent(window);
}
