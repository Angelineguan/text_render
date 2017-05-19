#pragma once
#include "stdafx.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height);

	~FrameBuffer();	

	void bindFrameBuffer();

	void unbindFrameBuffer();

	void bindColorBuffer();

	void bindDepthBuffer();

private:
	GLuint  m_fboHandle;
	GLuint	m_colorbufferhandle;
	GLuint  m_depthbufferhandle;

	int m_width;
	int m_height;
};