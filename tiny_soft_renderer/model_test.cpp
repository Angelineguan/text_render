#include "stdfax.h"
#include "util.h"

int main()
{
	TGAImage image = TGAImage(800, 600, TGAImage::RGBA);

	ObjModel* model = new ObjModel("obj/african_head/african_head.obj");

	ModelRenderMode mode;
	image.clear();
	mode = ModelRenderMode_RandomColor;
	model->drawModel(&image, mode, NULL);
	
	vec3f lightDir = vec3f(0, 0.0, -1.0f);
	image.clear();
	mode = ModelRenderMode_DirectionLight;
	model->drawModel(&image, mode, (void*)&lightDir);

	image.clear();
	mode = ModelRenderMode_NormalMap;
	model->drawModel(&image, mode, NULL);

	delete model;

	cout << "we start test function" << endl;
}