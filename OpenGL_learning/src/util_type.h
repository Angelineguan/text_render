#pragma once

struct Rect
{
	int left;
	int top;
	int width;
	int height;
	Rect(int l, int t, int w, int h)
	{
		left = l;
		top = t;
		width = w;
		height = h;
	}
};

Rect Rect_make(int l, int t, int w, int h)
{
	return Rect(l, t, w, h);
}
