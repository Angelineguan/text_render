#pragma  once
#include "stdafx.h"

class GraphicContext
{
public:
	static GraphicContext* instance();

	static DrawContext* getContext();

	static void freeGraphicContext();

	void setSize(vec2i size);

	void setCallbackCollections();

	RsProgram* getModelPrograme();

	RsProgram* getModelProgrameInstance();

	RsProgram* getTrianglePrograme();

	RsProgram* getParticleProgrameInstance();

	static void saveScreenToBmp(int x, int y, int width, int height);

protected:
	GraphicContext(int width, int height);

	~GraphicContext();

public:
	RsProgram* m_trianglePrograme;
	RsProgram* m_modelPrograme;
	RsProgram* m_modelProgrameInstance;
	RsProgram* m_particleProgrameInstance;

private:
	DrawContext* m_context;
};