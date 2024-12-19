#include "../global.h"
#include "../internals/window_internal.h"

struct
{
	uint32_t window_width;
	uint32_t window_height;
	Camera render_camera;
} g_GlobalState;

float global_aspect_ratio() {
	return float(g_GlobalState.window_width)/g_GlobalState.window_height;
}

int global_get_framerate()
{
	return int(1/time_get_deltatime());
}

void _window_intr_set_global_resolution_(uint32_t x, uint32_t y)
{
	g_GlobalState.window_width = x;
	g_GlobalState.window_height = y;
}

Camera& global_camera()
{
  return g_GlobalState.render_camera;
}
