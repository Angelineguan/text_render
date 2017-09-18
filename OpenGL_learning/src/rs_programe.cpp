#include "rs_programe.h"

RsProgram::RsProgram( const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource )
{
	m_program = createProgram(vertexShaderSource, fragmentShaderSource);
}

GLuint RsProgram::createProgram(const GLchar*_vertexShaderSource,const GLchar*_fragmentShaderSource)
{
	GLuint vertexShader; 
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &_vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success=0;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout<<"ERROR::verteshader::vertext::compile failed\n"<<infoLog<<endl;
	}
	/////////
	GLuint fragmentShader;
	fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &_fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout<<"ERROR::fragmentshader::vertext::compile failed\n"<<infoLog<<endl;
	}

	GLuint program;
	program=glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout<<"ERROR::SHADER_Progarem_GL_LINK_STATUS\n"<<infoLog<<endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

RsProgram::~RsProgram()
{
	cout<<"we are now delete the shader program"<<endl;
	glDeleteProgram(m_program);
}
