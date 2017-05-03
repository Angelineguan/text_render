#include "stdfax.h"
#include "util.h"

const int width = 800;
const int height = 800;

void drawObjModel(Model* model, TGAImage* image)
{
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		vec2f screen_coords[3];
		for (int j = 0; j < 3; j++) {
			Vec3f v = model->vert(face[j]);
			screen_coords[j].x = (v.x + 1.)*width / 2.;
			screen_coords[j].y = (v.y + 1.)*height / 2.;
		}
		drawTriangle_Crossproduct_Side(screen_coords[0], screen_coords[1], screen_coords[2],
			image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}
	image->flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image->write_tga_file("model_test.tga");
}

vec3i world2Screen(vec3f worldPos, int screenWidth, int screenHeight)
{
	vec3i screenPos;
	screenPos.x = (int)((worldPos.x + 1) * screenWidth / 2 + 0.5f);
	screenPos.y = (int)((worldPos.y + 1) * screenHeight / 2 + 0.5f);
	screenPos.z = (int)(worldPos.z + 0.5f);
	return screenPos;
}

void drawObjModel_LightIntensity(Model* model, TGAImage* image, vec3f lightDir)
{
	for (int i = 0; i < model->nfaces(); i++)
	{
		vec2f screen_coords[3];
		vec3f world_coords[3];
		std::vector<int> tempFace = model->face(i);
		vec3f v;
		for (int j = 0; j < 3; j++) 
		{
			v = model->vert1(tempFace[j]);
			world_coords[j] = v;
			screen_coords[j].x = (v.x + 1.)*width / 2.;
			screen_coords[j].y = (v.y + 1.)*height / 2.;
		}
		
		vec3f faceNormal = vec3f::crossProduct(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
		faceNormal.normalize();
		lightDir.normalize();

		float instensity = faceNormal * lightDir ;

		if (instensity >= 0)
		{
		drawTriangle_Crossproduct_Side(screen_coords[0], screen_coords[1], screen_coords[2],
			image, TGAColor(instensity * 255, instensity * 255, instensity * 255, 255));
		//drawTriangle_Crossproduct_Side(screen_coords[0], screen_coords[1], screen_coords[2],
		//	image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
		}
	}
	image->flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image->write_tga_file("model_light_test.tga");
}

int main()
{
	TGAImage image = TGAImage(width, height, TGAImage::RGBA);
	TGAColor fillColor = TGAColor(255, 0, 0, 255);
	TGAColor outlineColor = TGAColor(0, 255, 0, 255);
	vec3f lightDir = vec3f(0, 0.0, -1.0f);

	Model* model = new Model("obj/african_head/african_head.obj");

//	drawObjModel(model, &image);
	drawObjModel_LightIntensity(model, &image, lightDir);
	delete model;
	cout << "we start test function" << endl;
}