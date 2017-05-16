#include "color.h"

Color Color_make(float r, float g, float b, float a)
{
	return Color(r, g, b, a);
}

Color Random_Color()
{
	return Color_make(rand() % 255 / 255.0f, rand() % 255 / 255.0f
		, rand() % 255 / 255.0f, 1.0f);
}