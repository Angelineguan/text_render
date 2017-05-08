#include <iostream>
#include <fstream>
#include <sstream>
#include "obj_model.h"
#include "util.h"

ObjModel::ObjModel(const char *filename) 
{
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            vec3f v;
			for (int i = 0; i<3; i++) iss >> v.x >> v.y >> v.z;
            m_verts.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            vec3f n;
			for (int i = 0; i<3; i++) iss >> n.x >> n.y >> n.z;
            m_norms.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            vec2f uv;
			for (int i = 0; i<2; i++) iss >> uv.x >> uv.y;
            m_uv.push_back(uv);
        }  else if (!line.compare(0, 2, "f ")) {
            std::vector<Vertex> face;
			Vertex tri;
            iss >> trash;
			while (iss >> tri.vertexIndex >> trash >> tri.uvIndex >> trash >> tri.normalIndex) {
				tri.vertexIndex--;	// in wavefront obj all indices start at 1, not zero
				tri.uvIndex--;	// in wavefront obj all indices start at 1, not zero
				tri.normalIndex--;	// in wavefront obj all indices start at 1, not zero
				face.push_back(tri);
            }
			m_faces.push_back(face);
        }
    }
    std::cerr << "# v# " << m_verts.size() << " f# "  << m_faces.size() << " vt# " << m_uv.size() << " vn# " << m_norms.size() << std::endl;
    loadTexture(filename, "_diffuse.tga", m_diffusemap);
    loadTexture(filename, "_nm_tangent.tga",      m_normalmap);
    loadTexture(filename, "_spec.tga",    m_specularmap);
}

ObjModel::~ObjModel() {}

int ObjModel::nverts() 
{
    return (int)m_verts.size();
}

int ObjModel::nfaces() 
{
    return (int)m_faces.size();
}

std::vector<Vertex> ObjModel::face(int idx)
{
	std::vector<Vertex> face;
    for (int i=0; i<(int)m_faces[idx].size(); i++) face.push_back(m_faces[idx][i]);
    return face;
}

vec3f ObjModel::vert(int i) 
{
	return m_verts[i];
}

vec3f ObjModel::vert(int iface, int nthvert) 
{
    return m_verts[m_faces[iface][nthvert].vertexIndex];
}

void ObjModel::loadTexture(std::string filename, const char *suffix, TGAImage &img) 
{
    std::string texfile(filename);
    size_t dot = texfile.find_last_of(".");
    if (dot!=std::string::npos) {
        texfile = texfile.substr(0,dot) + std::string(suffix);
        std::cerr << "texture file " << texfile << " loading " << (img.readTgaFile(texfile.c_str()) ? "ok" : "failed") << std::endl;
        img.flipVertically();
    }
}

TGAColor ObjModel::diffuse(vec2f uvf) 
{
    vec2i uv((int)(uvf.x*m_diffusemap.getWidth()), (int)(uvf.y*m_diffusemap.getHeight()));
    return m_diffusemap.get(uv.x, uv.y);
}

vec3f ObjModel::normal(vec2f uvf) 
{
	vec2i uv((int)(uvf.x*m_diffusemap.getWidth()), (int)(uvf.y*m_diffusemap.getHeight()));
    TGAColor c = m_normalmap.get(uv.x, uv.y);
    vec3f res;
	res.x = (float)c[0] / 255.f*2.f - 1.f;
	res.y = (float)c[1] / 255.f*2.f - 1.f;
	res.z= (float)c[2] / 255.f*2.f - 1.f;
    return res;
}

vec3f ObjModel::normal(int iface, int nthvert) 
{
    int idx = m_faces[iface][nthvert].normalIndex;
	vec3f normal = m_norms[idx];
	normal.normalize();
    return normal;
}

vec2f ObjModel::uv(int iface, int nthvert)
{
    return m_uv[m_faces[iface][nthvert].uvIndex];
}

float ObjModel::specular(vec2f uvf) 
{
	vec2i uv((int)(uvf.x*m_diffusemap.getWidth()), (int)(uvf.y*m_diffusemap.getHeight()));
    return m_specularmap.get(uv.x, uv.y)[0]/1.f;
}

void ObjModel::drawModel(TGAImage* image, ModelRenderMode mode, void* userdata)
{
	int width = image->getWidth();
	int height = image->getHeight();
	for (int i = 0; i < nfaces(); i++)
	{
		vec2f screenCoords[3];
		vec3f worldCoords[3];
		vec3f normalCoords[3];
		std::vector<Vertex> tempFace = face(i);
		vec3f v;
		for (int j = 0; j < 3; j++)
		{
			v = vert(tempFace[j].vertexIndex);
			if (mode == ModelRenderMode_DirectionLight)
				worldCoords[j] = v;
			if (mode == ModelRenderMode_NormalMap)
			{
				normalCoords[j] = normal(i,j);
			}
			screenCoords[j].x = (v.x + 1.0f)*width / 2.0f;
			screenCoords[j].y = (v.y + 1.0f)*height / 2.0f;
		}

		switch (mode)
		{
			case ModelRenderMode_RandomColor:
				drawTriangle_Crossproduct_Side(screenCoords[0], screenCoords[1], screenCoords[2],
												image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
				break;
			case ModelRenderMode_DirectionLight:
			{
				vec3f faceNormal = vec3f::crossProduct(worldCoords[2] - worldCoords[0], worldCoords[1] - worldCoords[0]);
				faceNormal.normalize();
				vec3f lightDir = *(vec3f*)userdata;
				lightDir.normalize();

				float instensity = faceNormal * lightDir;
				if (instensity >= 0)
				{
					drawTriangle_Crossproduct_Side(screenCoords[0], screenCoords[1], screenCoords[2],
							image, TGAColor((int)(instensity * 255), (int)(instensity * 128), (int)(instensity * 255), 255));
				}
				break;
			}
			case ModelRenderMode_NormalMap:
			{
				vec3f normal;
				normal.setZero();
				for (int i = 0; i < 3; i ++)
				{
					normal = normal + normalCoords[i];
				}
				normal.normalize();
				drawTriangle_Crossproduct_Side(screenCoords[0], screenCoords[1], screenCoords[2],
					image, TGAColor((int)(normal.x * 255), (int)(normal.x * 255), (int)(normal.x* 255), 255));
				break;
			}
		}
			
	}
	image->flipVertically(); // i want to have the origin at the left bottom corner of the image
	image->writeTgaFile("model_normal_test.tga");
}
