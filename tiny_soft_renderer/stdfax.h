#pragma once
#include "tgaimage.h"
#include <iostream>
#include <algorithm>

using namespace std;

struct vec2f
{
	float x;
	float y;

	vec2f operator-(const vec2f& right)
	{
		vec2f temp;
		temp.x = this->x - right.x;
		temp.y = this->y - right.y;
		return temp;
	}

	float operator*(const vec2f& right)
	{
		return this->x * right.x + this->y * right.y;
	}

	vec2f operator*(float val)
	{
		vec2f temp;
		temp.x = this->x*val;
		temp.y = this->y*val;
		return temp;
	}

	vec2f operator+(const vec2f& right)
	{
		vec2f temp;
		temp.x = this->x + right.x;
		temp.y = this->y + right.y;
		return temp;
	}
	float length()
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	static vec2f normalize(vec2f v)
	{
		vec2f temp;
		float length = v.length();
		if (v.length() < 0.001f)
		{
			temp = { 0,0 };
			return temp;
		}
		temp.x = v.x / v.length();
		temp.y = v.y / v.length();
		return temp;
	}
};
	
typedef vec2f Point;
