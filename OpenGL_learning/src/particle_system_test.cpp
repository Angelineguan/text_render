#include "stdafx.h"
#include "particle_system.h"

int main()
{
	DrawContext* drawContext = GraphicContext::getContext();

	ParticleSystem* particleSystem = new ParticleSystem(15, 10.0f);

	int width, height;
		
	glfwGetFramebufferSize(drawContext, &width, &height);

	glEnable(GL_SCISSOR_TEST);

	while (!glfwWindowShouldClose(drawContext))
	{
		vec2i size;

		glfwGetWindowSize(drawContext, &size.x, &size.y);
		glScissor(0, 0, size.x, size.y);
		glViewport(0, 0, size.x, size.y);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


	/*	glScissor(100, 100, 400, 400);
		glViewport(100, 100, 400, 400);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
*/

		particleSystem->render();

		glfwPollEvents();
		glfwSwapBuffers(drawContext);

	}
	GraphicContext::saveScreenToBmp(0, 0, 800, 800);
	GraphicContext::freeGraphicContext();

	delete particleSystem;
	return 0;
}
