#pragma  once
#include "stdfax.h"


void drawLine(int x0, int y0, int x1, int y1, TGAImage* image, TGAColor color);
void drawLine(vec2f p0, vec2f p1, TGAImage* image, TGAColor color);

void drawTriangle(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor);

void drawTriangle_Crossproduct_Side(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor fillColor);

void drawCircle(vec2i center, int radius, TGAImage* image, TGAColor fiilColor);

vec3i world2Screen(vec3f worldPos, int screenWidth, int screenHeight);

vec3f calculateBarycentricCoordinate(vec3f p1, vec3f p2, vec3f p3, vec3f p);

void drawTriangle_GroundShading(vec2f p1, vec2f p2, vec2f p3, TGAImage* image, TGAColor p1Color, TGAColor p2Color, TGAColor p3Color);

void drawTriangle_GroundShading(vec2f* pts, TGAImage* image, TGAColor* ptColors);

void drawTriangle_Texture(vec2f* pts, TGAImage* image, vec2f* ptUvs, TGAImage* texture);