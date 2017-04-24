#pragma  once
#include "stdafx.h"

class Object
{
public:
	Object() {};
	virtual ~Object() {};

	virtual void draw() = 0;
	virtual void setIsDrawOutline(bool isDrawOutline) = 0;
	virtual void setInnerColor(Color color) = 0;
	virtual void setOutLineColor(Color color) = 0;
	virtual void setOffset(Vector3* offset) = 0;
};

