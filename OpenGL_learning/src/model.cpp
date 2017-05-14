#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphic_context.h"

const GLchar vertexShaderSrc[] = {
	"#version 330 core						\n"
	"in vec3 vertexPos;						\n"
	"void main()							\n"
	"{										\n"
	"	gl_Position=vec4(vertexPos,1.0f);	\n"
	"}										\n"
	"\0										\n"
};

const GLchar fragmentShaderSrc[] = {
	"uniform vec4 vertexColor;						\n"
	"out vec4 color;							\n"
	"void main()								\n"
	"{											\n"
	"	color=vertexColor;							\n"
	"}											\n"
	"\0											\n"
};

Model::Model(const char *filename) :m_programe(NULL), m_positionLoc(SIZE_MAX),
			m_colorLoc(SIZE_MAX)
{
	loadObjModel(filename);

	glGenBuffers(1, &m_vbo); 
	glBindBuffer(GL_VERTEX_ARRAY, m_vbo);
	glBufferData(GL_VERTEX_ARRAY, sizeof(vec3f) * m_verts.size(), &m_verts, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_vertIndex.size(), &m_vertIndex, GL_STATIC_DRAW);

	GraphicContext* context = GraphicContext::instance();
	if (context->m_modelPrograme == NULL)
	{
		context->m_modelPrograme = new RsProgram(vertexShaderSrc, fragmentShaderSrc);
	}

	m_programe = context->m_modelPrograme;

	m_positionLoc = m_programe->getAttributeLoc("vertexPos");
	assert(m_positionLoc != SIZE_MAX);

	m_colorLoc = m_programe->getUniformLoc("vertexColor");
	assert(m_colorLoc != SIZE_MAX);
}

void Model::loadObjModel(const char* filename)
{
	std::ifstream in;

	std::string objfilename(filename);
	objfilename = objfilename + std::string("african_head.obj");

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
			for (int i = 0; i < 3; i++) iss >> v.x >> v.y >> v.z;
			m_verts.push_back(v);
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