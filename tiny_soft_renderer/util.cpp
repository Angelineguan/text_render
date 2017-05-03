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
//bresenham algorithm for line rasterize
void drawLine(vec2f p0, vec2f p1, TGAImage* image, TGAColor color)
{
	if (p0.x == p1.x)
	{
		if (p0.y > p1.x) std::swap(p0, p1);
		for (int y = (int)p0.y; y < (int)p1.y; y++)
			image->set((int)p0.x, y, color);

		return;
	}
	else
	{
		if (p0.x > p1.x) std::swap(p0, p1);

		float k = (float)(p1.y - p0.y) / (float)(p1.x - p0.x);
		float b = p0.y - k * p0.x;

		float dy = p1.y - p0.y;
		float dx = p1.x - p0.x;
		float delt = abs(dy / dx);
		float erro = delt - 0.5f;
		int y = (int)p0.y;
		for (int x = (int)p0.x; x <= (int)p1.x; x++)
		{
			image->set(x, y, color);
			erro += delt;
			if (erro > 0.5f)
			{
				erro -= 1.0;
				y += 1;
			}
		}
	}
}

vec3f calculateBarycentricCoordinate(vec2f p1, vec2f p2, vec2f p3, vec2f p)
{
	float area1 = 0.5f * vec2f::crossProduct(p2 - p, p3 - p)/ (p2 - p).length() * (p3 - p).length();
	float area2 = 0.5f * vec2f::crossProduct(p3 - p, p1 - p)/ (p1 - p).length() * (p3 - p).length();
	float area3 = 0.5f * vec2f::crossProduct(p1 - p, p2 - p)/ (p1 - p).length() * (p2 - p).length();

	float sum = area1 + area2 + area3;
	return vec3f(area1 / sum, area2 / sum, area3 / sum);
}

TGAColor getColorFromUv(TGAImage* image, vec2f uv)
{
	float width = image->getWidth();
	float height = image->getHeight();
	return image->get((int)(uv.x * width), (int)(uv.y * height));
}

//http://www.sunshine2k.de/coding/java/PointInTriangle/PointInTriangle.html
//this is the artical point in triangle "Crossproduct Side Algorithm"
bool pointInTriangle(vec2f p1, vec2f p2, vec2f p3, vec2f p)
{
	vec2f U = p2 - p1;
	vec2f V = p3 - p1;

	vec2f C = p - p1;

	float s, t;

	t = (C.x * U.y - C.y * U.x) / (V.x*U.y - V.y*U.x);

	s = (C.x - V.x * t) / U.x;
	return s >= 0 && t >= 0 && (s + t) <= 1.0;
}

//Barycentric Algorithm for triangle rasterize
void drawTriangle_Crossproduct_Side(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor)
{
	float xmin, xmax, ymin, ymax;
	xmin = xmax = ymin = ymax = 0.0f;

	xmin = min(min(p1.x, p2.x), p3.x);
	ymin = min(min(p1.y, p2.y), p3.y);
	
	xmax = max(max(p1.x, p2.x), p3.x);
	ymax = max(max(p1.y, p2.y), p3.y);
	
	for (int y = (int)ymin; y <= (int)ymax; y++)
	{
		for (int x = (int)xmin; x <= (int)xmax; x++)
		{
			if (pointInTriangle(p1, p2, p3, vec2f((float)x, (float)y)))
				image->set(x, y, fillColor);
		}
	}
}

void drawTriangleWithTexture(vec2f* pts, vec2f* uv, TGAImage* image, TGAImage* texure)
{
	float xmin, xmax, ymin, ymax;
	xmin = xmax = ymin = ymax = 0.0f;
	vec2f p1 = pts[0];
	vec2f p2 = pts[1];
	vec2f p3 = pts[2];

	xmin = min(min(p1.x, p2.x), p3.x);
	ymin = min(min(p1.y, p2.y), p3.y);

	xmax = max(max(p1.x, p2.x), p3.x);
	ymax = max(max(p1.y, p2.y), p3.y);

	for (int y = (int)ymin; y <= (int)ymax; y++)
	{
		for (int x = (int)xmin; x <= (int)xmax; x++)
		{
			vec2f p((float)x, (float)y);
			if (pointInTriangle(p1, p2, p3, p))
			{
				vec3f baryCentric = calculateBarycentricCoordinate(p1, p2, p3, p);
				vec2f uvCoord = uv[0] * baryCentric.x + uv[1] * baryCentric.y + uv[2] * baryCentric.z;
				image->set(x, y, getColorFromUv(texure,uvCoord));
			}
		}
	}
}

//http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
//this is the algorithm for triangle rasterize
void drawTriangle(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor)
{
	// sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
	if (p1.y > p2.y) std::swap(p1, p2);
	if (p1.y > p3.y) std::swap(p1, p3);
	if (p2.y > p3.y) std::swap(p2, p3);

	int total_height = (int)(p3.y - p1.y);

	// draw bottom flat triangle
	for (int y = (int)p1.y; y <= (int)p2.y; y++) {
		int segment_height = (int)(p2.y - p1.y + 1);
		float alpha = (float)(y - p1.y) / total_height;
		float beta = (float)(y - p1.y) / segment_height; // be careful with divisions by zero 
		vec2f A = p1 + (p3 - p1)*alpha;
		vec2f B = p1 + (p2 - p1)*beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = (int)A.x; j <= (int)B.x; j++) {
			image->set(j, y, fillColor); // attention, due to int casts t0.y+i != A.y 
		}
	}

	// draw top flat triangle
	for (int y = (int)p2.y; y <= (int)p3.y; y++) {
		int segment_height = (int)(p3.y - p2.y + 1);
		float alpha = (float)(y - p1.y) / total_height;
		float beta = (float)(y - p2.y) / segment_height; // be careful with divisions by zero 
		vec2f A = p1 + (p3 - p1)*alpha;
		vec2f B = p2 + (p3 - p2)*beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = (int)A.x; j <= (int)B.x; j++) {
			image->set(j, y, fillColor); // attention, due to int casts t0.y+i != A.y 
		}
	}
}

void drawCircle(vec2i center, int radius, TGAImage* image, TGAColor fiilColor)
{
	int xmin, xmax;
	int ymin, ymax;

	xmin = center.x - radius;
	xmax = center.x + radius;

	ymin = center.y - radius;
	ymax = center.y + radius;

	int radiusSuqare = radius * radius;
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			if (vec2i::distanceSuqare(vec2i(x, y), center) < radiusSuqare)
			{
				image->set(x, y, fiilColor);
			}
		}
	}

}

vec3i world2Screen(vec3f worldPos, int screenWidth, int screenHeight)
{
	vec3i screenPos;
	screenPos.x = (int)((worldPos.x + 1) * screenWidth / 2 + 0.5f);
	screenPos.y = (int)((worldPos.y + 1) * screenHeight / 2 + 0.5f);
	screenPos.z = (int)(worldPos.z + 0.5f);
	return screenPos;
}


