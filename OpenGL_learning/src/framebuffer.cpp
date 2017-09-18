#include "framebuffer.h"

FrameBuffer::FrameBuffer( int width, int height ) : m_width(width), m_height(height)
{
	glGenFramebuffers(1,&m_fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER,m_fboHandle);	

	glGenTextures(1,&m_colorbufferhandle);
	glBindTexture(GL_TEXTURE_2D,m_colorbufferhandle);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,(GLsizei)m_width,(GLsizei)m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_colorbufferhandle,0);
	glBindTexture(GL_TEXTURE_2D,0);

	glGenRenderbuffers(1,&m_depthbufferhandle);
	glBindRenderbuffer(GL_RENDERBUFFER,m_depthbufferhandle);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,(GLsizei)m_width,(GLsizei)m_height);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_depthbufferhandle);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER==GL_FRAMEBUFFER_COMPLETE))
	{
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

FrameBuffer::~FrameBuffer() 
{
	glDeleteFramebuffers(1,&m_fboHandle);
	glDeleteBuffers(1, &m_colorbufferhandle);
	glDeleteBuffers(1, &m_depthbufferhandle);
}

void FrameBuffer::bindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER,m_fboHandle);
}

void FrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::bindColorBuffer() {
	glBindTexture(GL_TEXTURE_2D,m_colorbufferhandle);
}

void FrameBuffer::bindDepthBuffer() {
	glBindTexture(GL_RENDERBUFFER,m_depthbufferhandle);
}