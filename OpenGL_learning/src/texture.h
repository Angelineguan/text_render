#pragma once
#include "stdafx.h"
#include "vector2.h"

enum TextureWrap
{
	TextureWrap_CLAMP_TO_EDGE = 0,
	TextureWrap_CLAMP_TO_BORDER = 1,
	TextureWrap_REPEAT = 2,
	TextureWrap_MIRRORED_REPEAT= 3,
};

enum TextureFilter
{
	TextureFilter_LINEAR = 0,
	TextureFilter_NEAREST = 1,
};

class Texture
{
public:
	Texture(int width,int height,TextureWrap wrap, TextureFilter filter);

	Texture(GLchar* imageName, TextureWrap wrap, TextureFilter filter);

	~Texture();

	void bindTexture() {
		glBindTexture(GL_TEXTURE_2D, m_tex);
	}

	SizeI getTextureSize() {
		SizeI size;
		size.width = m_width;
		size.height= m_height;
		return size;
	}

	GLuint getTexture() {
		return m_tex;
	}

private:
	Texture();
	void _createTexture();
	void _createTexture(GLchar* imageName);
	TextureFilter m_filterMode;
	TextureWrap m_wrapMode;

	GLuint m_tex;
	int m_width;
	int m_height;
	int m_channel;
};