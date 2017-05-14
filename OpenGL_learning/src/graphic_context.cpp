#include "graphic_context.h"

static GraphicContext* g_context = NULL;

GraphicContext* GraphicContext::instance()
{
	if (g_context == NULL)
	{
		g_context = new GraphicContext(800, 600);
	}

	return g_context;
}

void GraphicContext::freeGraphicContext()
{
	if (g_context != NULL)
	{
		delete g_context;
	}
}

GraphicContext::GraphicContext(int width, int height)
{
	if (!glfwInit())
		return ;

	m_context = glfwCreateWindow(width, height, "Learn OpenGL", nullptr, nullptr);
	if (!m_context)
	{
		cout << "create window failed" << endl;
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(m_context);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << " failed to initialize the GLEW" << endl;
		glfwTerminate();
		return ;
	}

	m_trianglePrograme = NULL; 
	m_modelPrograme = NULL;
}

GraphicContext::~GraphicContext()
{
	glfwDestroyWindow(m_context);
	glfwTerminate();

	if (m_trianglePrograme != NULL)
	{
		delete m_trianglePrograme;
	}

	if (m_modelPrograme != NULL)
	{
		delete m_modelPrograme;
	}
}

DrawContext* GraphicContext::getContext()
{
	if (g_context == NULL)
	{
		g_context = new GraphicContext(800, 600);
	}
	return g_context->m_context;
}