#include "heat_map.h"
#include "texture.h"

GLchar heatMapVertexShaderSrc[] =
{
	"#version 330 core						\n"
	"in vec3 inPos;							\n"
	"uniform float inRadius;\n"
	"uniform vec2 inCenter;	\n"
	"uniform vec2 inWindowSize; \n"
	"out vec2 center; \n"
	"out float radius; \n"
	"void main()							\n"
	"{										\n"
	"	vec3 pos = vec3(inPos.x * (2 * inRadius / inWindowSize.x),inPos.y * (2 * inRadius / inWindowSize.y),0); \n"
	"	vec2 offset = 2 * inCenter / inWindowSize  - 1 ;\n"
	"	gl_Position = vec4(pos.x +offset.x ,pos.y +offset.y, 0,1.0); 		\n"
	"	radius = inRadius; \n"
	"	center = inCenter; \n"
	"}										\n"
	"\0										\n"
};

GLchar heatMapFragShaderSrc[] =
{
"vec3 fromRedToGreen(float interpolant)\n"
"{\n"
"if (interpolant < 0.5)\n"
"{\n"
"	return vec3(1.0, 2.0 * interpolant, 0.0); \n"
"}\n"
"else\n"
"{\n"
"	return vec3(2.0 - 2.0 * interpolant, 1.0, 0.0); \n"
"}\n"
"}\n"

"vec3 fromGreenToBlue(float interpolant)\n"
"{\n"
"	if (interpolant < 0.5)\n"
"	{\n"
"		return vec3(0.0, 1.0, 2.0 * interpolant);\n"
"	}\n"
"	else\n"
"	{\n"
"		return vec3(0.0, 2.0 - 2.0 * interpolant, 1.0);\n"
"	}\n"
"}\n"

"vec3 heat5(float interpolant)\n"
"{\n"
"	float invertedInterpolant = interpolant; \n"
"	if (invertedInterpolant < 0.5)\n"
"	{\n"
"		float remappedFirstHalf = 1.0 - 2.0 * invertedInterpolant; \n"
"		return fromGreenToBlue(remappedFirstHalf); \n"
"	}\n"
"	else\n"
"	{\n"
"		float remappedSecondHalf = 2.0 - 2.0 * invertedInterpolant; \n"
"		return fromRedToGreen(remappedSecondHalf); \n"
"	}\n"
"}\n"

"vec3 heat7(float interpolant)\n"
"{\n"
"	if (interpolant < 1.0 / 6.0)\n"
"	{\n"
"		float firstSegmentInterpolant = 6.0 * interpolant; \n"
"		return (1.0 - firstSegmentInterpolant) * vec3(0.0, 0.0, 0.0) + firstSegmentInterpolant * vec3(0.0, 0.0, 1.0); \n"
"	}\n"
"	else if (interpolant < 5.0 / 6.0)\n"
"	{\n"
"		float midInterpolant = 0.25 * (6.0 * interpolant - 1.0); \n"
"		return heat5(midInterpolant); \n"
"	}\n"
"	else\n"
"	{\n"
"		float lastSegmentInterpolant = 6.0 * interpolant - 5.0; \n"
"		return (1.0 - lastSegmentInterpolant) * vec3(1.0, 0.0, 0.0) + lastSegmentInterpolant * vec3(1.0, 1.0, 1.0); \n"
"	}\n"
"}\n"

"out vec4 outColor;						\n"
"in vec2 center; \n"
"in float radius; \n"
"uniform float inWeight; \n"
"void main()							\n"
"{										\n"
//"	vec2 uv = gl_FragCoord.xy / inWindowSize;\n"
//"	float interpolant = uv.x; \n"
//"	if (uv.y < 0.33)\n"
//"		outColor = (1.0 - interpolant) * vec4(0.0, 0.0, 1.0, 1.0) + interpolant * vec4(1.0, 0.0, 0.0, 1.0); \n"
//"	else if (uv.y < 0.66)\n"
//"		outColor = vec4(heat5(interpolant), 1.0); \n"
//"	else\n"
//"		outColor = vec4(heat7(interpolant), 1.0); \n"
//"	vec2 center = 0.5f * inWindowSize;\n "
//"	float radius = 100.0f;	\n"
"	float distance = length(gl_FragCoord.xy - center); \n"
"	float interpolant = distance / radius; \n"
//"	if (interpolant <= 0.33)\n"
//"		outColor = (1.0 - interpolant) * vec4(0.0, 0.0, 1.0, 1.0) + interpolant * vec4(1.0, 0.0, 0.0, 1.0); \n"
//"	else if (interpolant <= 0.66)\n"
//"		outColor = vec4(heat5(interpolant), 1.0); \n"
"	 if (interpolant < 1)\n"
"		outColor = vec4(heat5(1-interpolant), 1.5 - interpolant); \n"
"	else	\n"
"		outColor = vec4(0.,0,0,0.0); \n"
"}										\n"
};

GLfloat points[] = {
	-1.0f, -1.0f, 0,
	1.0f, -1.0f, 0,
	1.0f, 1.0f, 0,
	-1.0f, -1.0f, 0,
	1.0f, 1.0f, 0,
	-1.0f, 1.0f, 0
};


HeatMap::HeatMap(int pointNum) : m_heatPointNum(pointNum), m_shaderPrograme(NULL),
		m_mapColorTex(NULL),m_posLoc(-1), m_radiusLoc(-1), m_weightLoc(-1)
{
	init();
}

void HeatMap::init()
{
	m_heatPoint = new HeatPoint[m_heatPointNum];

	for (int i = 0 ; i < m_heatPointNum; i++)
	{
		m_heatPoint[i].center = { (float)(rand() % 1800), (float)(rand() % 1800) };
		m_heatPoint[i].weight = (float)(rand() % 256 / 256.0f);
		m_heatPoint[i].radius = (float)(rand() % 100 + 100);
		//m_heatPoint[i].center = vec2f(100.0f + (i + 1)  * 50, 400);
		//m_heatPoint[i].radius = 60;
	}

	m_shaderPrograme = new RsProgram(heatMapVertexShaderSrc, heatMapFragShaderSrc);
	assert(m_shaderPrograme != NULL);
	m_posLoc = m_shaderPrograme->getAttributeLoc("inPos");
	m_colorTexLoc = m_shaderPrograme->getAttributeLoc("inColorTex");

	m_weightLoc = m_shaderPrograme->getUniformLoc("inWeight");
	m_windowSizeLoc = m_shaderPrograme->getUniformLoc("inWindowSize");
	m_centerLoc = m_shaderPrograme->getUniformLoc("inCenter");
	m_radiusLoc = m_shaderPrograme->getUniformLoc("inRadius");

	m_mapColorTex = new Texture("heat_map_color.png", TextureWrap_CLAMP_TO_EDGE, TextureFilter_NEAREST);
	assert(m_mapColorTex != NULL);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(m_posLoc);

	m_shaderPrograme->setUniform2fv(m_centerLoc, vec2f(400, 400));
	m_shaderPrograme->setUniform1f(m_radiusLoc, 100);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

HeatMap ::~HeatMap()
{
	delete[] m_heatPoint;
	delete m_mapColorTex;
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_heatPointVbo);
}

void HeatMap::render(int width, int height)
{
	glScissor(0, 0, width, height);

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shaderPrograme->usePrograme();
	glBindVertexArray(m_vao);
	for (int i = 0; i< m_heatPointNum; i++)
	{
		m_shaderPrograme->setUniform2fv(m_windowSizeLoc, vec2f(width, height));
		m_shaderPrograme->setUniform2fv(m_centerLoc, m_heatPoint[i].center);
		m_shaderPrograme->setUniform1f(m_radiusLoc, m_heatPoint[i].radius);
		m_shaderPrograme->setUniform1f(m_weightLoc, m_heatPoint[i].weight);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
		glBindVertexArray(0);
}
