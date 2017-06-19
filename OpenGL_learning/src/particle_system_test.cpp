#include "stdafx.h"
#include "particle_system.h"

int main()
{
	DrawContext* drawContext = GraphicContext::getContext();

	ParticleSystem* particleSystem = new ParticleSystem(25, 10.0f);

	int width, height;
		
	glfwGetFramebufferSize(drawContext, &width, &height);

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(drawContext))
	{
		vec2i size;

		glfwGetWindowSize(drawContext, &size.x, &size.y);
		glScissor(0, 0, size.x, size.y);
		glViewport(0, 0, size.x, size.y);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


	/*	glScissor(100, 100, 400, 400);
		glViewport(100, 100, 400, 400);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
*/
		particleSystem->simulation(0.008f);
		particleSystem->render(size.x, size.y);

		glfwPollEvents();
		glfwSwapBuffers(drawContext);
	}
	GraphicContext::saveScreenToBmp(0, 0, 800, 800);
	GraphicContext::freeGraphicContext();

	delete particleSystem;
	return 0;
}
