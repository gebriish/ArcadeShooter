#include "../internals/event_internal.h"
#include "../event.h"

Event _event_intr_create_resize_(i32 width, i32 height) {
	Event e {
		.type = EventType::RESIZE
	};
	e.resizeData = {width, height};
	return e;
}

Event _event_intr_create_scroll_(f64 x, f64 y) {
	Event e {
		.type = EventType::SCROLL
	};
	e.scrollData = {x, y};
	return e;
}

Event _event_intr_create_cursor_move_(f64 x, f64 y, f64 dx, f64 dy) {
	Event e {
		.type = EventType::CURSOR
	};
	e.cursorMoveData = {x, y, dx, dy};
	return e;
}

Event _event_intr_create_mouse_button_(i32 button, i32 action, i32 mods) {
	Event e {
		.type = EventType::MOUSE_BUTTON
	};
	e.mouseButtonData = {button, action, mods};
	return e;
}

Event _event_intr_create_key_(i32 key, i32 scancode, i32 action, i32 mods) {
	Event e {
		.type = EventType::KEY
	};
	e.keyData = {key, scancode, action, mods};
	return e;
}

Event _event_intr_create_character_(char character) {
	Event e = {
		.type = EventType::CHARACTER
	};
	e.charData = {character};
	return e;
}
