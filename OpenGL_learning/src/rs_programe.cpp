#include "rs_programe.h"

RsProgram::RsProgram( const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource )
{
	m_program = createProgram(vertexShaderSource, fragmentShaderSource);
}

GLuint RsProgram::createProgram(const GLchar*_vertexShaderSource,const GLchar*_fragmentShaderSource)
{
	GLuint verteshader; 
	verteshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(verteshader, 1, &_vertexShaderSource, NULL);
	glCompileShader(verteshader);
	GLint success=0;
	GLchar infoLog[512];
	glGetShaderiv(verteshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(verteshader, 512, NULL, infoLog);
		cout<<"ERROR::verteshader::vertext::compile failed\n"<<infoLog<<endl;
	}
	/////////
	GLuint fragmentshader;
	fragmentshader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &_fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		cout<<"ERROR::fragmentshader::vertext::compile failed\n"<<infoLog<<endl;
	}

	GLuint program;
	program=glCreateProgram();
	glAttachShader(program, verteshader);
	glAttachShader(program, fragmentshader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout<<"ERROR::SHADER_Progarem_GL_LINK_STATUS\n"<<infoLog<<endl;
	}
	glDeleteShader(verteshader);
	glDeleteShader(fragmentshader);
	return program;
}

RsProgram::~RsProgram()
{
	cout<<"we are now delete the shader program"<<endl;
	glDeleteProgram(m_program);
}

GLuint RsProgram::getShaderProgram()
{ 
	return m_program; 
}

void RsProgram::usePrograme() 
{
	glUseProgram(m_program);
}

GLuint RsProgram::getUniformLoc(GLchar* name) 
{
	return glGetUniformLocation(m_program, name);
}

GLuint RsProgram::getAttributeLoc(GLchar* name) 
{
	return glGetAttribLocation(m_program, name);
}

void RsProgram::setUniform1f(GLuint loc, float value) 
{
	glUniform1f(loc, value);
}

void RsProgram::setUniform2fv(GLuint loc, vec2f vec) {
	glUniform2f(loc, vec.x, vec.y);
}

void RsProgram::setUniform2f(GLuint loc, float v0, float v1) 
{
	glUniform2f(loc, v0, v1);
}

void RsProgram::setUniform3fv(GLuint loc, float* vec) 
{
	glUniform3fv(loc, 3, vec);
}

void RsProgram::setUniform3fv(GLuint loc, vec3f vec) 
{
	setUniform3f(loc, vec.x, vec.y, vec.z);
}

void RsProgram::setUniform3f(GLuint loc, float v0, float v1, float v2)
{
	glUniform3f(loc, v0, v1, v2);
}

void RsProgram::setUniform4fv(GLuint loc, float* vec)
{
	glUniform4fv(loc, 4, vec);
}

void RsProgram::setUniform4fv(GLuint loc, vec4f vec)
{
	setUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void RsProgram::setUniform4f(GLuint loc, float v1, float v2, float v3, float v4)
{
	glUniform4f(loc, v1, v2, v3, v4);
}

void RsProgram::setAttribute1f(GLuint loc, float value)
{
	glVertexAttrib1f(loc, value);
}

void RsProgram::setAttribute3fv(GLuint loc, float* value)
{
	glVertexAttrib3fv(loc, value);
}

void RsProgram::setAttribute3f(GLuint loc, float x, float y, float z) 
{
	glVertexAttrib3f(loc, x, y, z);
}

void RsProgram::setVertexBuffer(GLuint loc, int size, GLvoid* val)
{
	glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, size*sizeof(float), val);
	glEnableVertexAttribArray(loc);
}
