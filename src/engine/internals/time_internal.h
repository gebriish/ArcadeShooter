#pragma once
#include <inttypes.h>
#include <GLFW/glfw3.h>

struct {	
	float delta_time;
	float frame_begin_time;
} g_Time;

void _time_intr_init();