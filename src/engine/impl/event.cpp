#include "../internals/event_internal.h"
#include "../event.h"

Event _event_intr_create_resize_(int width, int height) {
	Event e {
		.type = EventType::RESIZE
	};
	e.resizeData = {width, height};
	return e;
}

Event _event_intr_create_scroll_(double x, double y) {
	Event e {
		.type = EventType::SCROLL
	};
	e.scrollData = {x, y};
	return e;
}

Event _event_intr_create_cursor_move_(double x, double y, double dx, double dy) {
	Event e {
		.type = EventType::CURSOR
	};
	e.cursorMoveData = {x, y, dx, dy};
	return e;
}

Event _event_intr_create_mouse_button_(int button, int action, int mods) {
	Event e {
		.type = EventType::MOUSE_BUTTON
	};
	e.mouseButtonData = {button, action, mods};
	return e;
}

Event _event_intr_create_key_(int key, int scancode, int action, int mods) {
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
