#include "graphic_context.h"

#include "tgaimage.h"

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
	m_modelProgrameInstance = NULL;
	m_particleProgrameInstance = NULL;
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
		g_context = new GraphicContext(800, 800);
	}
	return g_context->m_context;
}

RsProgram* GraphicContext::getTrianglePrograme()
{
	if (m_trianglePrograme == NULL)
	{
		GLchar* vertexShader_drawTriangle =
		{
			"#version 330 core						\n"
			"in vec3 position;						\n"
			"uniform vec3 offset;						\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position=vec4(0.5*position.x+offset.x,0.5*position.y+offset.y,0.5*position.z+offset.z,1.0);		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar* fragmentShader_drawTriangle = 
		{
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
		GLchar vertexShaderSrc[] = 
		{
			"#version 330 core						\n"
			"in vec3 vertexPos;						\n"
			"in vec4 inVertexColor;					\n"
			"uniform vec2 inOffset;					\n"
			"out vec4 outVertexColor;				\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position=vec4(vertexPos.x * 0.4f - inOffset.x,vertexPos.y * 0.4f -  inOffset.y,vertexPos.z * 0.4f,1.0f);	\n"
			//"	gl_Position=vec4(vertexPos,1.0f);	\n"
			"	outVertexColor = inVertexColor;		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar fragmentShaderSrc[] = 
		{
			"out vec4 color;							\n"
			"in vec4 outVertexColor;				\n"
			"void main()								\n"
			"{											\n"
			"	color = outVertexColor;					\n"
			//"	color = vec4(1.0f,1.0f,1.0f,1.0f);					\n"
			"}											\n"
			"\0											\n"
		};
		m_modelPrograme = new RsProgram(vertexShaderSrc, fragmentShaderSrc);
	}

	return m_modelPrograme;
}


RsProgram* GraphicContext::getModelProgrameInstance()
{
	if (m_modelProgrameInstance == NULL)
	{
		GLchar vertexShaderSrc[] =
		{
			"#version 330 core						\n"
			"in vec3 vertexPos;						\n"
			"in vec4 inVertexColor;					\n"
			"in vec2 inOffset;				\n"
			"out vec4 outVertexColor;				\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position=vec4(vertexPos.x * 0.4f - inOffset.x,vertexPos.y * 0.4f -  inOffset.y,vertexPos.z * 0.4f,1.0f);	\n"
			"	outVertexColor = inVertexColor;		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar fragmentShaderSrc[] =
		{
			"out vec4 color;							\n"
			"in vec4 outVertexColor;				\n"
			"void main()								\n"
			"{											\n"
			"	color = outVertexColor;					\n"
			"}											\n"
			"\0											\n"
		};
		m_modelProgrameInstance = new RsProgram(vertexShaderSrc, fragmentShaderSrc);
	}

	return m_modelProgrameInstance;
}

//RsProgram* GraphicContext::getParticleProgrameInstance()
//{
//	if (m_particleProgrameInstance == NULL)
//	{
//		GLchar particleVetexShader[] =
//		{
//			"#version 330 core						\n"
//			"in vec3 inParticleCenter;				\n"
//			"in float inParticleRadius;				\n"
//			"in vec4 inParticleColor;				\n"
//			"in float inParticleAge;				\n"
//			"out float particleAge;				\n"
//			"out vec3 particleCenter;				\n"
//			"out vec4 particleColor;			\n"
//			"out float particleRadius;				\n"
//			"void main()							\n"
//			"{										\n"
//			"	gl_Position = vec4(inParticleCenter,1.0f); 		\n"
//			"	particleCenter = inParticleCenter; 		\n"
//			"	particleRadius = inParticleRadius; 		\n"
//			"	particleColor = inParticleColor; 		\n"
//			"	particleAge = inParticleAge; 		\n"
//			"}										\n"
//			"\0										\n"
//		};
//
//		GLchar particleFragShader[] =
//		{
//			"in float particleAge;					\n"
//			"in float particleRadius;				\n"
//			"in vec3 particleCenter;				\n"
//			"in vec4 particleColor;					\n"
//			"out vec4 color;						\n"
//			"void main()							\n"
//			"{										\n"
//			"	if ( abs(particleAge - 0.0f) <= 0.00001f && pow(gl_FragCoord.x - particleCenter.x,2) + pow(gl_FragCoord.y - particleCenter.y,2) > pow(particleRadius,2)) \n"
//			"		color = particleColor;			\n"
//			"	else								\n"
//			"		discard;						\n"
//			"}										\n"
//		};
//		m_particleProgrameInstance = new RsProgram(particleVetexShader, particleFragShader);
//	}
//
//	return m_particleProgrameInstance;
//}

RsProgram* GraphicContext::getParticleProgrameInstance()
{
	if (m_particleProgrameInstance == NULL)
	{
		GLchar particleVetexShader[] =
		{
			"#version 330 core						\n"
			"in vec3 inParticleCenter;				\n"
			"void main()							\n"
			"{										\n"
			"	gl_Position = vec4(inParticleCenter,1.0f); 		\n"
			"}										\n"
			"\0										\n"
		};

		GLchar particleFragShader[] =
		{
			"out vec4 color;						\n"
			"void main()							\n"
			"{										\n"
			"color = vec4(1.0f,1.0f,0.0f,1.0f); \n"
			"}										\n"
		};
		m_particleProgrameInstance = new RsProgram(particleVetexShader, particleFragShader);
	}

	return m_particleProgrameInstance;
}

void GraphicContext::saveScreenToBmp( int x, int y, int width, int height )
{
	//TGAImage image = TGAImage(width, height, TGAImage::RGBA);
	TGAImage image = TGAImage(width, height, TGAImage::GRAYSCALE);
	image.clear();

	//glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer());
	glReadPixels(x, y, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, image.buffer());
	image.flipVertically(); // i want to have the origin at the left bottom corner of the image
	image.writeTgaFile("model34.tga",false);
}

void GraphicContext::setSize(vec2i size)
{
	glfwSetWindowSize(g_context->getContext(), size.x, size.y);
}

