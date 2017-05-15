#pragma once
#include "stdafx.h"
#include "texture.h"
#include "rs_programe.h"

struct VertexIndex
{
	GLuint  vertexIndex;
	GLuint  uvIndex;
	GLuint  normalIndex;
};


class Model
{
public:
	Model(const char *filename);

	~Model();

	void draw(DrawContext* context);
protected:
	void loadObjModel(const char* filename);


private:
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;

	std::vector<vec3f> m_verts;
	std::vector<GLuint> m_vertIndex;

	vec3f* m_pts;
	int m_ptNum;
	GLuint* m_index;
	int m_indexNum;
	std::vector<vec3f> m_norms;
	std::vector<vec2f> m_uvs;
	std::vector<GLuint > m_normsIndex;
	std::vector<GLuint > m_uvsIndex;

	Texture* m_diffusemap;
	Texture* m_normalmap;
	Texture* m_specularmap;

private:
	RsProgram* m_programe;
	GLuint m_positionLoc;
	GLuint m_colorLoc;
};