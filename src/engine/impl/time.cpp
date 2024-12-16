#include "../time.h"
#include "../internals/time_internal.h"


void time_begin()
{
	_time_intr_init();
}

f32 time_get_time()
{
	return (f32) glfwGetTime();
}

f32 time_get_deltatime()
{
	return g_Time.delta_time;
}

void _time_intr_init()
{
    f32 currentTime = (f32) glfwGetTime();
    g_Time.delta_time = currentTime - g_Time.frame_begin_time;
    g_Time.frame_begin_time = currentTime;
}