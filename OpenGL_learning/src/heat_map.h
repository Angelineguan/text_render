#pragma once
#include "stdafx.h"

struct HeatPoint
{
	vec2f center;
	float radius;
	float weight;
};

class HeatMap
{
public:
	HeatMap(int pointNum);
	void render(int width, int height);

protected:
	~HeatMap();

private:
	void init();

	int m_heatPointNum;
	HeatPoint* m_heatPoint;
	Texture* m_mapColorTex;

	RsProgram* m_shaderPrograme;

	GLuint m_colorTexLoc;
	GLuint m_posLoc;
	GLuint m_radiusLoc;
	GLuint m_weightLoc;
	GLuint m_centerLoc;
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_windowSizeLoc;
	GLuint m_heatPointVbo;
};