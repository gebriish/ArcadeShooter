#pragma once
#include "../types.h"
#include <GLFW/glfw3.h>

struct {	
	f32 delta_time;
	f32 frame_begin_time;
} g_Time;

void _time_intr_init();