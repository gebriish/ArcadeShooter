#pragma once
#include "types.h"
#include "time.h"

struct Camera
{
};

f32 global_aspect_ratio();
u32 global_frame_rate();
void global_update_camera_projection();
void global_update_camera_view();
Camera& global_camera();
