#pragma once
#include "stdafx.h"

struct Color
{
	float red;
	float green;
	float blue;
	float alpha;

	Color() {};
	Color(float r, float g, float b, float a) :
		red(r), blue(b), green(g), alpha(a) {};
};

Color Color_make(float r, float g, float b, float a);

Color Random_Color();

