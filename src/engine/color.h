#pragma once
#include <cstdint>
#include "types.h"

struct Color 
{
	u8 r, g, b, a;
};

Color color_mix(const Color& a, const Color& b, float t);
Color color_from_hexcode(const char hexcode[6]);