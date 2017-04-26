#pragma once
#include "tgaimage.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct ivec2
{
	float x;
	float y;

	ivec2 operator-(const ivec2& right)
	{
		ivec2 temp;
		temp.x = this->x - right.x;
		temp.y = this->y - right.y;
		return temp;
	}

	float operator*(const ivec2& right)
	{
		return this->x * right.x + this->y * right.y;
	}

	ivec2 operator*(float val)
	{
		ivec2 temp;
		temp.x = this->x*val;
		temp.y = this->y*val;
		return temp;
	}

	ivec2 operator+(const ivec2& right)
	{
		ivec2 temp;
		temp.x = this->x + right.x;
		temp.y = this->y + right.y;
		return temp;
	}
	float length()
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}
};
	
typedef ivec2 Point;
