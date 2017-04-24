#include "graphic_context.h"
#include "callback_collections.h"

DrawContext* g_context;

DrawContext* GraphicContext_construct(int width,int height)
{
	if (!glfwInit())
		return NULL;

	g_context = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr,nullptr);
	if (!g_context)
	{
		cout<<"create window failed"<<endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(g_context);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout<<" failed to initialize the GLEW"<<endl;
		glfwTerminate();
		return NULL;
	}
	return g_context;
}

DrawContext* getGraphicContext()
{
	return g_context;
}

void Graphic_destruct()
{
	DrawContext* o = g_context;
	glfwDestroyWindow(o);
	glfwTerminate();
}

void setGraphicCallbackCollections()
{
	DrawContext*o = g_context;
	glfwSetKeyCallback(o,key_callback);
}

