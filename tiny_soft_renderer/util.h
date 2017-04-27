#pragma  once
#include "stdfax.h"

void drawLine(int x0, int y0, int x1, int y1, TGAImage* image, TGAColor color);
void drawLine(vec2f p0, vec2f p1, TGAImage* image, TGAColor color);

void drawTriangle(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor);

void drawTriangle_Crossproduct_Side(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor);

void drawCircle(vec2i center, int radius, TGAImage* image, TGAColor fiilColor);