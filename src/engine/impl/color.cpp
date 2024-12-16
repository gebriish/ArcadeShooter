#include "../color.h"
#include <stdio.h>

Color color_from_hexcode(const char hexcode[6])
{
	u32 r, g, b;
	sscanf(hexcode, "%02x%02x%02x", &r, &g, &b);
	Color c {(uint8_t)r,(uint8_t)g, (uint8_t)b, 255};
	return c;
};

Color color_mix(const Color& a, const Color& b, f32 t)
{
	Color c;
	c.r = u8(a.r + (b.r - a.r) * t);
	c.g = u8(a.g + (b.g - a.g) * t);
	c.b = u8(a.b + (b.b - a.b) * t);
	c.a = u8(a.a + (b.a - a.a) * t);
	return c;
}