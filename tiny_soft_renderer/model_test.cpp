#include "stdfax.h"
#include "util.h"

int main()
{
	TGAImage image = TGAImage(800, 600, TGAImage::RGBA);
	TGAColor fillColor = TGAColor(255, 0, 0, 255);
	TGAColor outlineColor = TGAColor(0, 255, 0, 255);
	vec3f lightDir = vec3f(0, 0.0, -1.0f);

	ObjModel* model = new ObjModel("obj/african_head/african_head.obj");

	//drawObjModel(model, &image);
	drawObjModel_LightIntensity(model, &image, lightDir);
	delete model;

	cout << "we start test function" << endl;
}