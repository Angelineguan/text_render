#include "texture.h"
#include "GL/SOIL.h"

Texture::Texture(int width,int height,TextureWrap wrap, TextureFilter filter)
	: m_width(width), m_height(height), m_wrapMode(wrap), m_filterMode(filter)
{
	m_tex = SIZE_MAX;
	_createTexture();
}

void Texture::_createTexture()
{
	glGenTextures(1,&m_tex);
	assert(m_tex != SIZE_MAX);

	glBindTexture(GL_TEXTURE_2D, m_tex);

	switch(m_wrapMode)
	{
		case TextureWrap_CLAMP_TO_BORDER:
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			break;
		case TextureWrap_CLAMP_TO_EDGE:
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		case TextureWrap_REPEAT:
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TextureWrap_MIRRORED_REPEAT:
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		default:
			break;
	}

	switch (m_filterMode)
	{
	case TextureFilter_LINEAR:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter_NEAREST:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_FLOAT, m_width, m_height, 0, GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glBindTexture(GL_TEXTURE_2D,0);
}

Texture::Texture(GLchar* imageName, TextureWrap wrap, TextureFilter filter)
	: m_wrapMode(wrap), m_filterMode(filter)
{
	assert(imageName == NULL);
	_createTexture(imageName);
}

void Texture::_createTexture(GLchar* imageName)
{
	glGenTextures(1,&m_tex);
	assert(m_tex != SIZE_MAX);

	glBindTexture(GL_TEXTURE_2D, m_tex);

	switch(m_wrapMode)
	{
	case TextureWrap_CLAMP_TO_BORDER:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	case TextureWrap_CLAMP_TO_EDGE:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case TextureWrap_REPEAT:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case TextureWrap_MIRRORED_REPEAT:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	default:
		break;
	}
	switch (m_filterMode)
	{
	case TextureFilter_LINEAR:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter_NEAREST:
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	unsigned char* image = SOIL_load_image(imageName, &m_width, &m_height,0,0);
	assert(m_tex == NULL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_FLOAT, m_width, m_height, 0, GL_RGBA,GL_UNSIGNED_BYTE,(void*)image);

	glBindTexture(GL_TEXTURE_2D,0);
}

