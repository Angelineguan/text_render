#pragma once 	
#include "stdafx.h"

class RsProgram
{
public:
	RsProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	~RsProgram();

	GLuint getShaderProgram() { return m_program; }

	void usePrograme() {
		glUseProgram(m_program);
	}

	GLuint getUniformLoc(GLchar* name) {
		return glGetUniformLocation(m_program, name);
	}

	GLuint getAttributeLoc(GLchar* name) {
		return glGetAttribLocation(m_program, name);
	}

	void setUniform1f(GLuint loc, float value) {
		glUniform1f(loc, value);
	}
	
	void setUniform2fv(GLuint loc, vec2f vec) {
		glUniform2f(loc, vec.x, vec.y);
	}
	void setUniform3fv(GLuint loc, float* vec) {
		glUniform3fv(loc, 3, vec);
	}

	void setUniform3fv(GLuint loc, vec3f vec) {
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}

	void setUniform3f(GLuint loc, float value1, float value2, float value3) {
		glUniform3f(loc, value1, value2, value3);
	}

	void setUniform4fv(GLuint loc, float* vec) {
		float temp;
		for (int i = 0; i < 4; i++)
		{
			temp = vec[i];
		}
		glUniform4fv(loc, 4, vec);
		glUniform4f(loc, vec[0], vec[1], vec[2], vec[3]);
	}

	void setUniform4fv(GLuint loc, vec4f vec) {
		glUniform4fv(loc, 4, (float*)&vec.x);
	}

	void setUniform4f(GLuint loc, float value1, float value2, float value3, float value4) {
		glUniform4f(loc, value1, value2, value3, value4);
	}


	void setAttribute1f(GLuint loc, float value) {
		glVertexAttrib1f(loc, value);
	}

	void setAttribute3fv(GLuint loc, float* value) {
		glVertexAttrib3fv(loc, value);
	}

	void setAttribute3f(GLuint loc, float x, float y, float z) {
		glVertexAttrib3f(loc, x, y, z);
	}

	void setVertexBuffer(GLuint loc, int size, GLvoid* val)
	{
		glVertexAttribPointer(loc,size,GL_FLOAT,GL_FALSE,size*sizeof(float),val);
		glEnableVertexAttribArray(loc);
	}

private:
	GLuint createProgram(const GLchar*_vertexShaderSource, const GLchar*_fragmentShaderSource);

	GLuint m_program;
};

