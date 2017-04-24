#include "stdafx.h"
#include "graphic_context.h"
#include "triangle.h"
#include "util.h"
#include "object.h"

extern GLfloat vertex[];
extern GLfloat vertex1[];

int main()
{
	DrawContext* drawContext = GraphicContext_construct(800, 600);
	Object* triange = new Triangle(vertex, 18);
	Object* triange1 = new Triangle(vertex1, 18);

	vec3 offset = vec3_makeZero();
	 
	triange->setOffset(&offset);
	triange1->setOffset(&offset);
	setGraphicCallbackCollections();
	int width, height;
	
	glfwGetFramebufferSize(drawContext, &width, &height);
	glViewport(0, 0, width, height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);   
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);   
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(drawContext))
	{
		glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		vec3 offset = vec3_makeZero();
		Color innerColor;
		innerColor = Color_make(1.0, 0.0, 0.0, 1.0);
		glfwPollEvents();  
		triange1->setInnerColor(innerColor);
		triange1->setOffset(&offset);
		triange1->setIsDrawOutline(true);
		triange1->draw();

		offset.x = 0.3f;
		offset.x = -0.3f;
		offset.z = 0.0f;
		innerColor = Color_make(0.0, 1.0, 0.0, 1.0);

		triange->setInnerColor(innerColor);
		triange->setOffset(&offset);
		triange->setIsDrawOutline(true);
		triange->draw();
		//////////////////////////////////////////////////////////////////////////
		glfwSwapBuffers(drawContext);
	}		
	Graphic_destruct();
	delete triange1;
	delete triange;

	return 0;
}