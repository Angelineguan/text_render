#include "callback_collections.h"

void key_callback(DrawContext*o,int key,int scancode,int action,int mode)
{
	static float lineWidth=1.0f;
	if (key==GLFW_KEY_ESCAPE&&action==GLFW_PRESS)
	{
		cout<<"we are going to exit the graphic context"<<endl;
		glfwSetWindowShouldClose(o,GL_TRUE);
	}
	if (key==GLFW_KEY_L&&action==GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	if (key==GLFW_KEY_F&&action==GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
	{
		if (lineWidth <= 10.0f)
			lineWidth += 0.5;
		glLineWidth(lineWidth);
		cout<<"lineWidth"<<lineWidth<<endl;
	}
	if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
	{
		if (lineWidth >= 0.0f)
			lineWidth -= 0.5;
		glLineWidth(lineWidth);

		cout<<"lineWidth"<<lineWidth<<endl;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		GLint a;
		glGetIntegerv(GL_BLEND,&a);
	}
	
}