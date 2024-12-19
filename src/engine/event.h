#pragma once

enum class EventType
{
  RESIZE = 0,
  CURSOR = 1,
  MOUSE_BUTTON = 2,
  KEY = 3,
  SCROLL = 4,
  CHARACTER = 5,
};


struct Event
{
  EventType type;

  union {
    struct { int width, height; } resizeData;
    struct { double xPos, yPos, Dx, Dy; } cursorMoveData;
    struct { int button, action, mods; } mouseButtonData;
    struct { int key, scancode, action, mods; } keyData;
    struct { double scrollX, scrollY; } scrollData;
    struct { char character; } charData;
  };
};