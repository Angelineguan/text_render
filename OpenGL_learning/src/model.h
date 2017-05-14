#pragma once
#include "stdafx.h"
#include "texture.h"
#include "rs_programe.h"

struct VertexIndex
{
	int vertexIndex;
	int uvIndex;
	int normalIndex;
};


class Model
{
public:
	Model(const char *filename);

	~Model();

protected:
	void loadObjModel(const char* filename);

private:
	GLuint m_vbo;
	GLuint m_ibo;

	std::vector<vec3f> m_verts;
	std::vector<vec3f> m_norms;
	std::vector<vec2f> m_uvs;
	std::vector<int> m_vertIndex;
	std::vector<int> m_normsIndex;
	std::vector<int> m_uvsIndex;

	Texture* m_diffusemap;
	Texture* m_normalmap;
	Texture* m_specularmap;

private:
	RsProgram* m_programe;
	GLuint m_positionLoc;
	GLuint m_colorLoc;
};