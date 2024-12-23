#include "../input.h"
#include "../internals/window_internal.h"
#include <GLFW/glfw3.h>

bool input_is_key_pressed(int key)
{
	bool valid;
	GLFWwindow* window_ptr = _window_intr_get_glfw_window(valid);

	if(valid)
		return glfwGetKey(window_ptr, key) == GLFW_PRESS;
	
	return false;
}

bool input_is_mouse_pressed(int button)
{
	bool valid;
	GLFWwindow* window_ptr = _window_intr_get_glfw_window(valid);

	if(valid)
		return glfwGetMouseButton(window_ptr, button) == GLFW_PRESS;
	
	return false;
}

std::pair<float, float> input_get_cursor_pos()
{
	double x, y;

	bool valid;
	GLFWwindow* window_ptr = _window_intr_get_glfw_window(valid);

	if(valid)
	{
		glfwGetCursorPos(window_ptr, &x, &y);
		return std::pair<float, float>(float(x), float(y));
	}
	
	return std::pair<float, float>(0.0, 0.0);
}

void input_set_cursor_mode(CursorMode mode)
{
	bool valid;
	GLFWwindow* window_ptr = _window_intr_get_glfw_window(valid);

	if(valid)
	{
		switch (mode)
		{
			case CursorMode::DISABLED:
				glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			case CursorMode::NORMAL:
				glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			case CursorMode::HIDDEN:
				glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;
		}
	}
}
