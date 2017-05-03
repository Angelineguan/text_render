#pragma once
#include "stdfax.h"


template<typename T>
class vector2
{
public:
	T x;
	T y;

	vector2() {}

	vector2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	vector2 operator-(const vector2& right)
	{
		vector2 temp;
		temp.x = this->x - right.x;
		temp.y = this->y - right.y;
		return temp;
	}

	T operator*(const vector2& right)
	{
		return this->x * right.x + this->y * right.y;
	}

	vector2 operator*(T val)
	{
		vector2 temp;
		temp.x = this->x*val;
		temp.y = this->y*val;
		return temp;
	}

	vector2 operator+(const vector2& right)
	{
		vector2 temp;
		temp.x = this->x + right.x;
		temp.y = this->y + right.y;
		return temp;
	}
	T length()
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	static vector2 normalize(vector2& v)
	{
		vector2 temp;
		T length = v.length();
		if (v.length() < 0.001f)
		{
			temp = { 0, 0 };
			return temp;
		}
		temp.x = v.x / v.length();
		temp.y = v.y / v.length();
		return temp;
	}

	static T distanceSuqare(const vector2& left, const vector2& right)
	{
		return (left.x - right.x) * (left.x - right.x)
			+ (left.y - right.y) * (left.y - right.y);
	}

	static T distance(const vector2& left, const vector2& right)
	{
		return sqrtf((left.x - right.x) * (left.x - right.x)
			+ (left.y - right.y) * (left.y - right.y));
	}
};

typedef vector2<float> vec2f;
typedef vector2<int> vec2i;
typedef vector2<double> vec2d;

