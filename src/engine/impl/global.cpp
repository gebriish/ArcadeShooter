#include "../global.h"
#include "../internals/window_internal.h"

struct
{
	u32 window_width;
	u32 window_height;
	Camera render_camera;
} g_GlobalState;

f32 global_aspect_ratio() {
	return f32(g_GlobalState.window_width)/g_GlobalState.window_height;
}

u32 global_frame_rate() {
	return u32(1/time_get_deltatime());
}

void _window_intr_set_global_resolution_(u32 x, u32 y)
{
	g_GlobalState.window_width = x;
	g_GlobalState.window_height = y;
}

Camera& global_camera()
{
  return g_GlobalState.render_camera;
}
