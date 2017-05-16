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

RsProgram* GraphicContext::getTrianglePrograme()
{
	if (m_trianglePrograme == NULL)
	{
		GLchar* vertexShader_drawTriangle = {
			"#version 330 core						\n"
			"in vec3 position;						\n"
			"uniform vec3 offset;						\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position=vec4(0.5*position.x+offset.x,0.5*position.y+offset.y,0.5*position.z+offset.z,1.0);		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar*fragmentShader_drawTriangle = {
			"uniform vec4 outColor;						\n"
			"out vec4 color;							\n"
			//	"uniform vec3 changeColor;					\n"
			"void main()								\n"
			"{										\n"
			"	color=vec4(outColor.x,outColor.y,outColor.z,outColor.w);						\n"
			"}										\n"
		};
		m_trianglePrograme = new RsProgram(vertexShader_drawTriangle, fragmentShader_drawTriangle);
	}

	return m_trianglePrograme;
}

RsProgram* GraphicContext::getModelPrograme()
{
	if (m_modelPrograme == NULL)
	{
		GLchar vertexShaderSrc[] = {
			"#version 330 core						\n"
			"in vec3 vertexPos;						\n"
			"in vec4 inVertexColor;					\n"
			"out vec4 outVertexColor;				\n"
			"void main()							\n"
			"{										\n"
			//"	gl_Position=vec4(vertexPos.x * 0.5f,vertexPos.y * 0.5f,vertexPos.z * 0.5f,1.0f);	\n"
			"	gl_Position=vec4(vertexPos,1.0f);	\n"
			"	outVertexColor = inVertexColor;		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar fragmentShaderSrc[] = {
			"uniform vec4 vertexColor;						\n"
			"out vec4 color;							\n"
			"in vec4 outVertexColor;				\n"
			"void main()								\n"
			"{											\n"
			//	"	color=vertexColor;							\n"
		//	"	color = outVertexColor;					\n"
			"	color = vec4(1.0f,1.0f,1.0f,1.0f);					\n"
			"}											\n"
			"\0											\n"
		};
		m_modelPrograme = new RsProgram(vertexShaderSrc, fragmentShaderSrc);
	}

	return m_modelPrograme;
}