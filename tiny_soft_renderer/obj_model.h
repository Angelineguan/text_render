#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include <string>
#include "tgaimage.h"
#include "vector2.h"
#include "vector3.h"

struct Vertex
{
	int vertexIndex;
	int uvIndex;
	int normalIndex;
};

enum ModelRenderMode
{
	ModelRenderMode_RandomColor = 1,
	ModelRenderMode_DirectionLight = 2,
	ModelRenderMode_NormalMap = 3
};

class ObjModel {
public:
    ObjModel(const char *filename);
    
	~ObjModel();
	
	int nverts();
    
	int nfaces();
	
	vec3f normal(int iface, int nthvert);
    
	vec2f uv(int iface, int nthvert);
    
	vec3f normal(vec2f uv);
	
	vec3f vert(int i);
    vec3f vert(int iface, int nthvert);
    TGAColor diffuse(vec2f uv);
    float specular(vec2f uv);
    std::vector<Vertex> face(int idx);

	void drawModel(TGAImage* image,ModelRenderMode mode, void* userdata);

private:
    std::vector<vec3f> m_verts;
    std::vector< std::vector<Vertex>> m_faces; // attention, this Vec3i means vertex/uv/normal
    std::vector<vec3f> m_norms;
    std::vector<vec2f> m_uv;
    TGAImage m_diffusemap;
    TGAImage m_normalmap;
    TGAImage m_specularmap;
    void loadTexture(std::string filename, const char *suffix, TGAImage &img);
};
#endif //__MODEL_H__

