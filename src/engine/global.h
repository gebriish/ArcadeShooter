#pragma once
#include "time.h"
#include "vmath.h"

struct Camera
{
	mat4 proj, view;
};

float global_aspect_ratio();
Camera& global_camera();
int global_get_framerate();
