#pragma once 	
#include "stdafx.h"

class RsProgram
{
public:
	RsProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);

	~RsProgram();

	GLuint getShaderProgram();

	void usePrograme();

	GLuint getUniformLoc(GLchar* name);

	GLuint getAttributeLoc(GLchar* name);

	void setUniform1f(GLuint loc, float value);
	
	void setUniform2fv(GLuint loc, vec2f vec);

	void setUniform2f(GLuint loc, float v0, float v1);

	void setUniform3fv(GLuint loc, float* vec);

	void setUniform3fv(GLuint loc, vec3f vec);

	void setUniform3f(GLuint loc, float v0, float v1, float v2);

	void setUniform4fv(GLuint loc, float* vec);

	void setUniform4fv(GLuint loc, vec4f vec);

	void setUniform4f(GLuint loc, float v1, float v2, float v3, float v4);

	void setAttribute1f(GLuint loc, float value);
	
	void setAttribute3fv(GLuint loc, float* value);

	void setAttribute3f(GLuint loc, float x, float y, float z);

	void setVertexBuffer(GLuint loc, int size, GLvoid* val);
	
private:
	GLuint createProgram(const GLchar*_vertexShaderSource, const GLchar*_fragmentShaderSource);

	GLuint m_program;
};

