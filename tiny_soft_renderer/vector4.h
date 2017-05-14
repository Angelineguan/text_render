#pragma once

template<typename T>
class vector4
{
public:
	T x;
	T y;
	T z;
	T w;

	vector4() {}

	vector4(T _x, T _y, T _z, T _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vector4 operator+(const vector4& right)
	{
		return vector4(x + right.x, y + right.y, z + right.z,w + right.w);
	}

	vector4 operator-(const vector4& right)
	{
		return vector4(x - right.x, y - right.y, z - right.z, w - right.w);
	}

	T operator*(const vector4& right)
	{
		return x * right.x + y * right.y + z * right.z + w * right * w;
	}

	vector4 operator*(T val)
	{
		return vector4(x * val, y * val, z * val, w * val);
	}

	T length()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	void normalize()
	{
		T l = length();
		if (l < 0.001f)
			return;

		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

	void setZero()
	{
		x = y = z = w =  0;
	}

	static T distanceSuqare(const vector4& left, const vector4& right)
	{
		return (left.x - right.x) * (left.x - right.x)
			+ (left.y - right.y) * (left.y - right.y)
			+ (left.z - right.z) * (left.z - right.z)
			+ (left.w - right.w) * (left.w - right.w);
	}

	static T distance(const vector4& left, const vector4& right)
	{
		return sqrtf((left.x - right.x) * (left.x - right.x)
			+ (left.y - right.y) * (left.y - right.y)
			+ (left.z - right.z) * (left.z - right.z)
			+ (left.w - right.w) * (left.w - right.w));
	}
	
};

typedef vector4<float> vec4f;
typedef vector4<int> vec4i;

