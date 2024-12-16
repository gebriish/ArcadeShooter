#pragma once
#include <GLFW/glfw3.h>
#include <queue>
#include "../event.h"

struct GlfwWindowWrapper {
	GLFWwindow* glfwWindow;
	std::queue<Event> eventQueue;	
};

GLFWwindow* _window_intr_get_glfw_window(bool &valid);
void _window_intr_set_global_resolution_(u32 x, u32 y);
void _window_intr_setup_event_callback_();
