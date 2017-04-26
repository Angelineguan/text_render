#include "util.h"

void drawLine(int x0, int y0, int x1, int y1, TGAImage* image, TGAColor color)
{
	if (x0 > x1)
	{
		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;
	}

	float k = (float)(y1 - y0) / (float)(x1 - x0);
	float b = y0 - k * x0;

	int y;
	for (int x = x0; x <= x1; x++)
	{
		y = (int)(k * x + b);
		image->set(x, y, color);
	}
}

void drawLine(ivec2 p0, ivec2 p1, TGAImage* image, TGAColor color)
{
	if (p0.x > p1.x)
	{
		ivec2 temp = p0;
		p0 = p1;
		p1 = temp;
	}
	float k = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);

	float b = p0.y - k * p0.x;

	int y;
	int lastY = 0;
	for (int x = p0.x; x <= p1.x;x++)
	{
		y = (int)(k * x + b);
		lastY = y;
	/*	if (y - lastY == 2 )
		{
			cout << "we have a bug here \n" << endl;
			y -= 1;
		}*/
		image->set(x, y, color);
	}
}

void drawTriangle(ivec2 p1, ivec2 p2, ivec2 p3, TGAImage* image, TGAColor fillColor)
{
// sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
	if (p1.y > p2.y) std::swap(p1, p2);
	if (p1.y > p3.y) std::swap(p1, p3);
	if (p2.y > p3.y) std::swap(p2, p3);
	int total_height = p3.y - p1.y;
	for (int y = p1.y; y <= p2.y; y++) {
		int segment_height = p2.y - p1.y + 1;
		float alpha = (float)(y - p1.y) / total_height;
		float beta = (float)(y - p1.y) / segment_height; // be careful with divisions by zero 
		ivec2 A = p1 + (p3 - p1)*alpha;
		ivec2 B = p1 + (p2 - p1)*beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) {
			image->set(j, y, fillColor); // attention, due to int casts t0.y+i != A.y 
		}
	}
	for (int y = p2.y; y <= p3.y; y++) {
		int segment_height = p3.y - p2.y + 1;
		float alpha = (float)(y - p1.y) / total_height;
		float beta = (float)(y - p2.y) / segment_height; // be careful with divisions by zero 
		ivec2 A = p1 + (p3 - p1)*alpha;
		ivec2 B = p2 + (p3 - p2)*beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) {
			image->set(j, y, fillColor); // attention, due to int casts t0.y+i != A.y 
		}
	}
}