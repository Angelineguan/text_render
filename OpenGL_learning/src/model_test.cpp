#include "stdafx.h"
#include "graphic_context.h"
#include "triangle.h"
#include "model.h"


int main()
{
	DrawContext* drawContext = GraphicContext::getContext();


	_chdir("obj/african_head/");
	Model* model = new Model("african_head.obj");

	int width, height;
		
	glfwGetFramebufferSize(drawContext, &width, &height);
	glViewport(0, 0, width, height);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(, GL_LINE);

	while (!glfwWindowShouldClose(drawContext))
	{
		glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		model->draw(drawContext);
		glfwSwapBuffers(drawContext);
	}

	GraphicContext::freeGraphicContext();

	return 0;
}