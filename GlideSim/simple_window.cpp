#include "simple_window.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "error.h"


using std::string;


// Window variables

GLFWwindow * window;

int WindowWidth = 0;
int WindowHeight = 0;


// Basic Callbacks

void error_callback(int code, const char * msg)
{
	string m = msg;

	m += " code : " + std::to_string(code);

	MsgBox(m.data(), "LIBRARY ERROR");
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


// Window handling

void initWindow(int width, int height, char * name)
{
	WindowWidth = width;
	WindowHeight = height;

	glfwSetErrorCallback(error_callback);

	int isInit;

	isInit = glfwInit();

	if (isInit == GLFW_FALSE)
	exit(EXIT_FAILURE);

	isInit = glfwInit();

	if (isInit == GLFW_FALSE)
	exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WindowWidth, WindowHeight, name, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
}

void closeWindow()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}

bool shouldClose()
{
	return glfwWindowShouldClose(window);
}

void swapBuffer()
{
	glfwSwapBuffers(window);
}


// OpenGL initialization

void initOGL()
{
	// GLEW

	glewExperimental = true;

	int isInit = glewInit();

	if (isInit != GLEW_OK)
		exit(EXIT_FAILURE);


	// OpenGL

	glViewport(0, 0, WindowWidth, WindowHeight);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0.4f, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}