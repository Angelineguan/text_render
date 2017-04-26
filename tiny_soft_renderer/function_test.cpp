#include "stdfax.h"
#include "util.h"

int main()
{
	TGAImage image = TGAImage(100, 100, TGAImage::RGBA);
	TGAColor fillColor = TGAColor(255, 0, 0, 255);
	TGAColor outlineColor = TGAColor(0, 255, 0, 255);
	//image.set(50, 50, red);
	vec2f p1 = { 20, 21 };
	vec2f p2 = { 59, 76 };
	vec2f p3 = { 90, 60 };
	vec2f p4 = { 5, 90 };
//	drawLine(p1, p2, &image,fillColor);
//	drawTriangle(p1, p2, p3, &image, outlineColor);
	//drawTriangle(p1, p4, p3, &image, fillColor);
	//drawTriangle(p4, p2, p3, &image, fillColor);
	drawTriangle1(p1, p2, p3, &image, outlineColor);

	//drawLine(20, 20, 79, 89, &image, fillColor);
	//drawLine(79, 20, 20, 89, &image, red);
	
	image.flip_vertically();
//	image.flip_horizontally();
	image.write_tga_file("test.tga");
	cout << "we start test function" << endl;
}