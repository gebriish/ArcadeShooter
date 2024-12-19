#pragma once

struct Event;

Event _event_intr_create_resize_(int width, int height);
Event _event_intr_create_scroll_(double x, double y);
Event _event_intr_create_cursor_move_(double x, double y, double dx, double dy);
Event _event_intr_create_mouse_button_(int button, int action, int mods);
Event _event_intr_create_key_(int key, int scancode, int action, int mods);
Event _event_intr_create_character_(char character);


