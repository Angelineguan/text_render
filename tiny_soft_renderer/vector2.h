#pragma once

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
		return vector2(x - right.x, y - right.y);
	}

	vector2 operator+(const vector2& right)
	{
		return vector2(x + right.x, y + right.y);
	}

	T operator*(const vector2& right)
	{
		return x * right.x + y * right.y;
	}

	vector2 operator*(T val)
	{
		return vector2(x * val, y * val);
	}

	bool operator==(const vector2& right)
	{
		return std::abs(x - right.x) <= 0.0001f && std::abs(y - right.y) <= 0.0001f;
	}

	T length()
	{
		return sqrtf(x * x + y * y);
	}

	void normalize()
	{
		T l = length();
		if (l < 0.001f)
			return;

		x /= l;
		y /= l;
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

	static T crossProduct(const vector2& left, const vector2& right)
	{
		return left.x * right.y - left.y * right.x;
	}
};

typedef vector2<float> vec2f;
typedef vector2<int> vec2i;

