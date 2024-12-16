#pragma once

#include "types.h"
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
	u32 width = 640;
	u32 height = 400;
	std::string title = "untitled";
	u16 flags = 0;
};

bool window_initialize(Window& window);
void window_destroy();

bool window_event_in_queue(Event& e);

bool window_should_close();
void window_swap_buffers();
void window_poll_events();
void window_resize_region(i32, i32, i32, i32);
void window_clear_viewport(f32, f32, f32, f32);
