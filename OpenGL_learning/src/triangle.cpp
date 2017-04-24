#include "triangle.h"
#include "vector3.h"

GLfloat vertex[]={
	-0.5f, -0.5f, 0,
	0.5f, -0.5f, 0,
	0,  0.5f, 0,
	0,  0.5f, 0,
	0.5f, -0.5f, 0,
	1.0f, 0.5f, 0
};

GLfloat vertex1[]={
	-0.5f, -0.5f, -0.5,
	0.5f, -0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0.5f, -0.5f,  -0.5,
	1.0f, 0.5f,  -0.5
};

const GLchar* vertexShader_drawTriangle={
	"#version 330 core						\n"
	"in vec3 position;						\n"
	"uniform vec3 offset;						\n"
	"void main()							\n"
	"{										\n"
	"	gl_Position=vec4(0.5*position.x+offset.x,0.5*position.y+offset.y,0.5*position.z+offset.z,1.0);		\n"
	"}										\n"
	"\0										\n"
} ;

const GLchar*fragmentShader_drawTriangle={
	"uniform vec4 outColor;						\n"
	"out vec4 color;							\n"
//	"uniform vec3 changeColor;					\n"
	"void main()								\n"
	"{										\n"
	"	color=vec4(outColor.x,outColor.y,outColor.z,outColor.w);						\n"
	"}										\n"
} ;

Triangle::Triangle( GLfloat* vertex, size_t num )
{
	m_programe  =  new RsProgram(vertexShader_drawTriangle, fragmentShader_drawTriangle);
	glGenVertexArrays(1, &m_vaoHandle);
	glBindVertexArray(m_vaoHandle);
	glGenBuffers(1, &m_vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*num, vertex, GL_STATIC_DRAW);

	GLuint shader  =  m_programe->getShaderProgram();
	GLint  vertxPosition;
	vertxPosition = glGetAttribLocation(shader, "position");
	glVertexAttribPointer(vertxPosition, 3, GL_FLOAT,GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(vertxPosition);
	glBindVertexArray(0);

	m_innerColor = Color_make(1.0, 0.0, 0.0, 1.0);
	m_outLineColor = Color_make(1.0, 0.0, 0.0, 1.0);
	m_offset = vec3_makeZero();
	m_isDrawOutline= false;
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &m_vboHandle);
	delete(m_programe);
}

void Triangle::draw()
{	
	m_programe->usePrograme();
	glBindVertexArray(m_vaoHandle);

	GLuint offsetPosition,colorPosition;

	offsetPosition = m_programe->getUniformLoc("offset");
	m_programe->setUniform3fv(offsetPosition,m_offset);

	colorPosition = m_programe->getUniformLoc("outColor");
	//////////////////////////////////////////////////////////////////////////
	if (m_isDrawOutline)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_programe->setUniform4fv(colorPosition,m_outLineColor);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	//////////////////////////////////////////////////////////////////////////
	static float red = 0.0f;
	static float green = 0.3f;
	static float blue = 0.8f;

	red += 0.00005f;
	green += 0.0005f;
	blue += 0.0005f;
	m_innerColor = Color_make(sinf(red), cosf(green), sinf(blue), 1.0f);

	float color[4] = { m_innerColor.red,m_innerColor.blue,m_innerColor.green,m_innerColor.alpha};
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	m_programe->setUniform4fv(colorPosition,m_innerColor);
	glDrawArrays(GL_TRIANGLES, 0 ,6);
	glBindVertexArray(0);
}

void Triangle::setInnerColor(Color color)
{
	m_innerColor = color;
}

void Triangle::setOutLineColor(Color color)
{
	m_outLineColor = color;
}

void Triangle::setOffset(vec3* offset)
{
	m_offset = *offset;
}
//////////////////////////////////////////////////////////////////////////
