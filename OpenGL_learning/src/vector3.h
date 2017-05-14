#pragma once

template<typename T>
class vector3
{
public:
	T x;
	T y;
	T z;

	vector3() {}

	vector3(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	vector3 operator+(const vector3& right)
	{
		return vector3(x + right.x, y + right.y, z + right.z);
	}

	vector3 operator-(const vector3& right)
	{
		return vector3(x - right.x, y - right.y, z - right.z);
	}

	T operator*(const vector3& right)
	{
		return x * right.x + y * right.y + z * right.z;
	}

	vector3 operator*(T val)
	{
		return vector3(x * val, y * val, z * val);
	}

	T length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void normalize()
	{
		T l = length();
		if (l < 0.001f)
			return ;

		x /= l;
		y /= l;
		z /= l;
	}

	void setZero()
	{
		x = y = z = 0;
	}

	static T distanceSuqare(const vector3& left, const vector3& right)
	{
		return (left.x - right.x) * (left.x - right.x)
			+ (left.y - right.y) * (left.y - right.y)
			+ (left.z - right.z) * (left.z - right.z);
	}

	static T distance(const vector3& left, const vector3& right)
	{
		return sqrtf((left.x - right.x) * (left.x - right.x)
				+ (left.y - right.y) * (left.y - right.y)
				+ (left.z - right.z) * (left.z - right.z));
	}

	static vector3 crossProduct(const vector3& left, const vector3& right)
	{
		return vector3(left.y * right.z - left.z * right.y,
			left.z * right.x - left.x * right.z,
			left.x * right.y - left.y * right.x);
	}
};

typedef vector3<float> vec3f;
typedef vector3<int> vec3i;