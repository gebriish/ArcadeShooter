#include "../color.h"
#include <stdio.h>

Color color_from_hexcode(const char hexcode[6])
{
	uint32_t r, g, b;
	sscanf(hexcode, "%02x%02x%02x", &r, &g, &b);
	Color c {(uint8_t)r,(uint8_t)g, (uint8_t)b, 255};
	return c;
};

Color color_mix(const Color& a, const Color& b, float t)
{
	Color c;
	c.r = uint8_t(a.r + (b.r - a.r) * t);
	c.g = uint8_t(a.g + (b.g - a.g) * t);
	c.b = uint8_t(a.b + (b.b - a.b) * t);
	c.a = uint8_t(a.a + (b.a - a.a) * t);
	return c;
}