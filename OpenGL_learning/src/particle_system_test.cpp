#include "stdafx.h"
#include "particle_system.h"
#include "triangle.h"
#include "heat_map.h"
GLfloat vertex0[] = {
	-0.5f, -0.5f, 0,
	0.5f, -0.5f, 0,
	0,  0.5f, 0,
	0,  0.5f, 0,
	0.5f, -0.5f, 0,
	1.0f, 0.5f, 0
};

GLfloat vertex1[] = {
	-0.5f, -0.5f, -0.5,
	0.5f, -0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0.5f, -0.5f,  -0.5,
	1.0f, 0.5f,  -0.5
};


int main()
{
	DrawContext* drawContext = GraphicContext::getContext();

	ParticleSystem* particleSystem = new ParticleSystem(50, 10.0f);
	Triangle*tri = new Triangle(vertex0, 6);
	HeatMap*heatMap = new HeatMap(18);
	tri->setIsDrawOutline(true);
	int width, height;
		
	glfwGetFramebufferSize(drawContext, &width, &height);

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(drawContext))
	{
		vec2i size;

		glfwGetWindowSize(drawContext, &size.x, &size.y);

		particleSystem->render(size.x, size.y);
		//tri->render();
		heatMap->render(size.x, size.y);
		glfwPollEvents();
		glfwSwapBuffers(drawContext);
	}
	GraphicContext::saveScreenToBmp(0, 0, 800, 800);
	GraphicContext::freeGraphicContext();

	delete particleSystem;
	delete tri;
	return 0;
}
