#pragma  once
#include "stdafx.h"
#include "rs_programe.h"

class GraphicContext
{
public:
	static GraphicContext* instance();

	static DrawContext* getContext();

	static void freeGraphicContext();

	void setCallbackCollections();
	RsProgram* getModelPrograme();

	RsProgram* getTrianglePrograme();

protected:
	GraphicContext(int width, int height);

	~GraphicContext();

public:
	RsProgram* m_trianglePrograme;
	RsProgram* m_modelPrograme;

private:
	DrawContext* m_context;
};