#include "simple_window.h"



#include <string>

#include "error.h"


using std::string;


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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		// The cursor entered the client area of the window
	}
	else
	{
		// The cursor left the client area of the window
	}
}


// Window handling

void SimpleWindow::initWindow(int width, int height, char * name)
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

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);

	glfwMakeContextCurrent(window);

	glfwSetCursorPos(window, WindowWidth / 2, WindowHeight / 2);

	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SimpleWindow::closeWindow()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}

bool SimpleWindow::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void SimpleWindow::swapBuffer()
{
	glfwSwapBuffers(window);
}


// OpenGL initialization

void SimpleWindow::initOGL()
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