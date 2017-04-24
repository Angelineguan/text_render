#pragma once
#include "stdafx.h"

class Vector3
{
public:
	Vector3(){}
	Vector3(const Vector3 &a):x(a.x),y(a.y),z(a.z){}
	Vector3(float _x,float _y,float _z):x(_x),y(_y),z(_z){}
	Vector3 &operator =(const Vector3 &a)
	{
		x=a.x;
		y=a.x;
		z=a.z;
		return *this;
	}
	bool operator==(const Vector3 &a)const
	{
		return x==a.x&&y==a.y&&z==a.z;
	}
	bool operator!=(const Vector3 &a)const
	{
		return x!=a.x||y!=a.y||z!=a.z;
	}
	void setZero()
	{
		x=y=z=0;
	}
	Vector3 operator-()const
	{
		return Vector3(-x,-y,-z);
	}
	Vector3 operator+(const Vector3 &a)const
	{
		return Vector3(x+a.x,y+a.y,z+a.z);
	}
	Vector3 operator-(const Vector3 &a)const
	{
		return Vector3(x-a.x,y-a.y,z-a.z);
	}
	Vector3 operator*(float a)const
	{
		return Vector3(a*x,a*y,a*z);
	}
	Vector3 operator/(float a)const
	{
		float factor=1.0f/a;
		return Vector3(factor*x,factor*y,factor*z);
	}
	Vector3 operator +=(const Vector3 &a)  
	{
		x+=a.x;
		y+=a.y;
		z+=a.z;
		return *this;
	}
	Vector3 operator -=(const Vector3 &a)  
	{
		x-=a.x;
		y-=a.y;
		z-=a.z;
		return *this;
	}
	Vector3 operator *=(float a)  
	{
		x*=a;
		y*=a;
		z*=a;
		return *this;
	}
	Vector3 operator /=(float a)  
	{
		float factor=1.0f/a;
		x*=factor;
		y*=factor;
		z*=factor;
		return *this;
	}

	void normalize()
	{
		float lengthSquare=x*x+y*y+z*z;
		if (lengthSquare>0)
		{
			float factor=1.0f/sqrt(lengthSquare);
			x*=factor;
			y*=factor;
			z*=factor;
		}
	}

	float operator * (const Vector3 &a) const
	{
		return x*a.x+y*a.y+z*a.z;
	}

	inline float length()
	{
		return sqrt(x*x+y*y+z*z);
	}
	
	inline float distance(const Vector3 &left,const Vector3 &right)
	{
		float dx=left.x-right.x;
		float dy=left.y-right.y;
		float dz=left.z-right.z;
		return sqrt(dx*dx+dy*dy+dz*dz);
	}

	float x;
	float y;
	float z;
};


