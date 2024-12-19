#pragma once

#include <inttypes.h>
#include "event.h"
#include <string>

enum WindowFlags
{
	WINDOWFLAGS_NONE 		= 0,
	WINDOWFLAGS_RESIZABLE 	= 1 << 1,
	WINDOWFLAGS_MAXIMIZED 	= 1 << 2,
	WINDOWFLAGS_UNDECORATED = 1 << 3,
	WINDOWFLAGS_VSYNC 		= 1 << 4,
	WINDOWFLAGS_CENTERED    = 1 << 5,
};

struct Window
{
	uint32_t width = 640;
	uint32_t height = 400;
	std::string title = "untitled";
	uint16_t flags = 0;
};

bool window_initialize(Window& window);
void window_destroy();

bool window_event_in_queue(Event& e);

bool window_should_close();
void window_swap_buffers();
void window_poll_events();
void window_resize_region(int, int, int, int);
void window_clear_viewport(float, float, float, float);
