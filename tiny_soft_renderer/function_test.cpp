#include "stdfax.h"
#include "util.h"

int main()
{
	TGAImage image = TGAImage(100, 100, TGAImage::RGBA);
	TGAColor fillColor = TGAColor(255, 0, 0, 255);
	TGAColor outlineColor = TGAColor(0, 255, 0, 255);
	//image.set(50, 50, red);
	ivec2 p1 = { 20, 21 };
	ivec2 p2 = { 59, 76 };
	ivec2 p3 = { 90, 60 };
	ivec2 p4 = { 5, 90 };
//	drawLine(p1, p2, &image,fillColor);
	drawTriangle(p1, p2, p3, &image, fillColor);
	drawTriangle(p1, p4, p3, &image, fillColor);
	drawTriangle(p4, p2, p3, &image, fillColor);
	//drawLine(20, 20, 79, 89, &image, red);
	//drawLine(79, 20, 20, 89, &image, red);
	
	image.flip_vertically();
//	image.flip_horizontally();
	image.write_tga_file("test.tga");
	cout << "we start test function" << endl;
}