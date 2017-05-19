#include "stdafx.h"
#include "graphic_context.h"
#include "triangle.h"
#include "model.h"
#include "framebuffer.h"


int main()
{
	_chdir("obj/african_head/");

	DrawContext* drawContext = GraphicContext::getContext();

	Model* model = new Model("african_head.obj");

	int width, height;
		
	glfwGetFramebufferSize(drawContext, &width, &height);
	FrameBuffer* fbo = new FrameBuffer(width, height);

	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_SCISSOR_TEST);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_ALWAYS); // Change this to whatever kind of depth testing you want
	glDepthRange(0.1f, 0.4f);
	glDepthRange(0.7f, 0.9f);

	while (!glfwWindowShouldClose(drawContext))
	{

		fbo->bindFrameBuffer();
		fbo->bindColorBuffer();

		glScissor(0, 0, 800, 800);
		glViewport(0, 0, 800, 800);
		glClearColor(1.0f, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model->draw(drawContext);
		fbo->unbindFrameBuffer();

		glScissor(100, 100, 400, 400);
		glViewport(100, 100, 400, 400);
		glClearColor(0, 1,0,1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model->draw(drawContext);

		glScissor(500, 500, 200, 200);
		glViewport(500, 500, 200, 200);
		glClearColor(0, 0, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model->draw(drawContext);

		glfwPollEvents();
		glfwSwapBuffers(drawContext);

	}
	fbo->bindFrameBuffer();
	GraphicContext::saveScreenToBmp(0, 0, 800, 800);
	GraphicContext::freeGraphicContext();
	return 0;
}