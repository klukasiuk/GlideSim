#include "input_handler.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "core.h"

InputHandler::InputHandler()
{
	mouse_input = false;
}

void InputHandler::process_input()
{
	int state;

	float movement_rate = 0.2f;

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_W);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(movement_rate, 0, 0);

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_S);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(-movement_rate, 0, 0);

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_A);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(0, 0, -movement_rate);

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_D);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(0, 0, movement_rate);

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_SPACE);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(0, movement_rate, 0);

	state = glfwGetKey(core::simpleWindow.window, GLFW_KEY_LEFT_CONTROL);
	if (state == GLFW_PRESS)
		core::renderer.cam.move(0, -movement_rate, 0);


	double xpos, ypos;
	glfwGetCursorPos(core::simpleWindow.window, &xpos, &ypos);

	int screen_center_x = core::simpleWindow.WindowWidth / 2;
	int screen_center_y = core::simpleWindow.WindowHeight / 2;

	double horizontalAngle = movement_rate * (screen_center_x - xpos);
	double verticalAngle   = movement_rate * (screen_center_y - ypos);

	core::renderer.cam.rotate(glm::vec3(0, verticalAngle, horizontalAngle));

	glfwSetCursorPos(core::simpleWindow.window, screen_center_x, screen_center_y);
}
