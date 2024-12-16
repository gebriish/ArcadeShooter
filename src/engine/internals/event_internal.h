#pragma once
#include "../types.h"

struct Event;

Event _event_intr_create_resize_(i32 width, i32 height);
Event _event_intr_create_scroll_(f64 x, f64 y);
Event _event_intr_create_cursor_move_(f64 x, f64 y, f64 dx, f64 dy);
Event _event_intr_create_mouse_button_(i32 button, i32 action, i32 mods);
Event _event_intr_create_key_(i32 key, i32 scancode, i32 action, i32 mods);
Event _event_intr_create_character_(char character);


