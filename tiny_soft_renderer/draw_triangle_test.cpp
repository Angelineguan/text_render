#include "stdfax.h"
#include "util.h"

int main()
{
	TGAImage image = TGAImage(800, 600, TGAImage::RGBA);

	vec2f pts[3];
	TGAColor ptColors[3];

	pts[0] = vec2f(100.0f, 100.0f);
	pts[1] = vec2f(200.0f, 600.0f);
	pts[2] = vec2f(600.0f, 500.0f);

	ptColors[0] = TGAColor(255, 0, 0, 255);
	ptColors[1] = TGAColor(255, 0, 0, 255);
	ptColors[2] = TGAColor(0, 0, 255, 255);
	
	image.clear();
	drawTriangle_GroundShading(pts, &image, ptColors);
	cout << "we start test function" << endl;


	TGAImage texture = TGAImage(800, 600, TGAImage::RGBA);
	if (!texture.readTgaFile("timg.tga"))
	{
		cout << "read image failed" << endl;
	}
	vec2f ptUvs[3];

	ptUvs[2] = vec2f(0.3f, 0.3f);
	ptUvs[1] = vec2f(0.6f, 0.6f);
	ptUvs[0] = vec2f(0.9f, 0.2f);
	image.clear();
	drawTriangle_Texture(pts, &image, ptUvs, &texture);
}