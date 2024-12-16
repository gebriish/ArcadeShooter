#pragma once
#include "types.h"

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
    struct { i32 width, height; } resizeData;
    struct { f64 xPos, yPos, Dx, Dy; } cursorMoveData;
    struct { i32 button, action, mods; } mouseButtonData;
    struct { i32 key, scancode, action, mods; } keyData;
    struct { f64 scrollX, scrollY; } scrollData;
    struct { char character; } charData;
  };
};