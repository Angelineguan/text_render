#pragma once
#include "stdafx.h"
#include "graphic_context.h"


struct VertexIndex
{
	GLuint  vertexIndex;
	GLuint  uvIndex;
	GLuint  normalIndex;
};

struct Vertex
{
	vec3f pos;
	Color color;
};

class Model
{
public:
	Model(const char *filename);

	~Model();

	void draw(DrawContext* context);
	void draw(DrawContext* context, vec2f offset);
	void draw(DrawContext* context, bool offset);
	void drawInstance(DrawContext* context);


protected:
	void loadObjModel(const char* filename);


private:
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;

	std::vector<vec3f> m_verts;
	std::vector<Vertex> m_vertsWithColor;
	std::vector<GLuint> m_vertIndex;

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
	GLuint m_offset;

	vec2f m_offsetVec[100000];
	GLuint m_offsetVbo;

};