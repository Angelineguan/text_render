#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<string.h>
using namespace std;

Model::Model(const char *filename) :m_programe(NULL), m_positionLoc(SIZE_MAX),
			m_colorLoc(SIZE_MAX)
{
	loadObjModel(filename);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo); 
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertsWithColor.size(), &m_vertsWithColor[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_vertIndex.size(), &m_vertIndex[0], GL_STATIC_DRAW);

	//m_programe = GraphicContext::instance()->getModelPrograme();
	m_programe = GraphicContext::instance()->getModelProgrameInstance();
	m_positionLoc = m_programe->getAttributeLoc("vertexPos");
	assert(m_positionLoc != SIZE_MAX);
	glVertexAttribPointer(m_positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(m_positionLoc);

	m_colorLoc = m_programe->getAttributeLoc("inVertexColor");
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)3);
	glEnableVertexAttribArray(m_colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int x = 0; x <= 100000; x += 1)
	{
		m_offsetVec[x] = { rand()%100 / 100.0f , rand() % 100 / 100.0f };
	}

	glGenBuffers(1, &m_offsetVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_offsetVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f) * 30000, &m_offsetVec[0], GL_STATIC_DRAW);
	m_offset = m_programe->getAttributeLoc("inOffset");
	glVertexAttribPointer(m_offset, 2, GL_FLOAT, GL_FALSE, sizeof(vec2f), (GLvoid*)0);
	glEnableVertexAttribArray(m_offset);

	glVertexAttribDivisor(m_offset, 100);

//	m_offset = m_programe->getUniformLoc("inOffset");
	glBindVertexArray(0);

}

void Model::loadObjModel(const char* filename)
{
	std::ifstream in;

	std::string objfilename(filename);

	in.open(objfilename, std::ifstream::in);
	if (in.fail()) return;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			vec3f v;
			Vertex vertex;
			for (int i = 0; i < 3; i++) iss >> v.x >> v.y >> v.z;
			{
				vertex.pos = v;
				vertex.color = Random_Color();
				m_verts.push_back(v);
				m_vertsWithColor.push_back(vertex);
			}
		}
		else if (!line.compare(0, 3, "vn ")) {
			iss >> trash >> trash;
			vec3f n;
			for (int i = 0; i < 3; i++) iss >> n.x >> n.y >> n.z;
			m_norms.push_back(n);
		}
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			vec2f uv;
			for (int i = 0; i < 2; i++) iss >> uv.x >> uv.y;
			m_uvs.push_back(uv);
		}
		else if (!line.compare(0, 2, "f ")) {
			//f 24 / 1 / 24 25 / 2 / 25 26 / 3 / 26
			std::vector<VertexIndex> face;
			VertexIndex tri;
			iss >> trash;
			while (iss >> tri.vertexIndex >> trash >> tri.uvIndex >> trash >> tri.normalIndex) {
				tri.vertexIndex--;	// in wavefront obj all indices start at 1, not zero
				tri.uvIndex--;	// in wavefront obj all indices start at 1, not zero
				tri.normalIndex--;	// in wavefront obj all indices start at 1, not zero
				
				m_vertIndex.push_back(tri.vertexIndex);
				m_normsIndex.push_back(tri.normalIndex);
				m_uvsIndex.push_back(tri.uvIndex);
			}
		}
	}

	std::string diffuseTexfile(filename);
	diffuseTexfile = diffuseTexfile + std::string("african_head_diffuse.jpg");
	m_diffusemap = new Texture((char*)diffuseTexfile.c_str(), TextureWrap_CLAMP_TO_EDGE, TextureFilter_NEAREST);

	std::string nm_tangentTexfile(filename);
	nm_tangentTexfile = nm_tangentTexfile + std::string("african_head_nm_tangent.jpg");
	m_normalmap = new Texture((char*)nm_tangentTexfile.c_str(), TextureWrap_CLAMP_TO_EDGE, TextureFilter_NEAREST);

	std::string specTexfile(filename);
	specTexfile = specTexfile + std::string("african_head_spec.jpg");
	m_specularmap = new Texture((char*)specTexfile.c_str(), TextureWrap_CLAMP_TO_EDGE, TextureFilter_NEAREST);
}

void Model::draw(DrawContext* context)
{
	m_programe->usePrograme();

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_vertIndex.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::draw(DrawContext* context, vec2f offset)
{
	m_programe->usePrograme();

	glBindVertexArray(m_vao);
	m_programe->setUniform2fv(m_offset, offset);
	glDrawElements(GL_TRIANGLES, m_vertIndex.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::draw(DrawContext* context, bool offset)
{
	m_programe->usePrograme();
	glBindVertexArray(m_vao);

	for (int i = 0; i < 10000; i++)
	{
		m_programe->setUniform2fv(m_offset, m_offsetVec[i]);
		glDrawElements(GL_TRIANGLES, m_vertIndex.size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Model::drawInstance(DrawContext* context)
{
	m_programe->usePrograme();
	glBindVertexArray(m_vao);

	glDrawElementsInstanced(GL_TRIANGLES, m_vertIndex.size(), GL_UNSIGNED_INT, 0, 30000);
	glBindVertexArray(0);
}


Model::~Model()
{
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}