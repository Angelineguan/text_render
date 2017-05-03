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

	vector3 operator-(const vector3& right)
	{
		vector3 temp;
		temp.x = this->x - right.x;
		temp.y = this->y - right.y;
		temp.z = this->z - right.z;
		return temp;
	}

	vector3 operator-(T val)
	{
		vector3 temp;
		temp.x = this->x - val;
		temp.y = this->y - val;
		temp.z = this->z - val;
		return temp;
	}

	T operator*(const vector3& right)
	{
		return this->x * right.x + this->y * right.y + this->z * right.z;
	}


	vector3 operator*(T val)
	{
		vector3 temp;
		temp.x = this->x*val;
		temp.y = this->y*val;
		temp.z = this->z*val;
		return temp;
	}

	vector3 operator+(const vector3& right)
	{
		vector3 temp;
		temp.x = this->x + right.x;
		temp.y = this->y + right.y;
		temp.z = this->z + right.z;
		return temp;
	}
	T length()
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	vector3 normalize()
	{
		T length = this->length();
		if (length < 0.001f)
		{
			return *this;
		}
		this->x /= length;
		this->y /= length;
		this->z /= length;
		return *this;
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
		vector3 temp;
		temp.x = left.y * right.z - left.z * right.y;
		temp.y = left.z * right.x - left.x * right.z;
		temp.z = left.x * right.y - left.y * right.x;
		return temp;
	}
};

typedef vector3<float> vec3f;
typedef vector3<int> vec3i;