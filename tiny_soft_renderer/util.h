#pragma  once
#include "stdfax.h"

void drawLine(int x0, int y0, int x1, int y1, TGAImage* image, TGAColor color);
void drawLine(ivec2 p0, ivec2 p1, TGAImage* image, TGAColor color);

void drawTriangle(ivec2 p1, ivec2 p2, ivec2 p3, TGAImage* image, TGAColor fillColor);
