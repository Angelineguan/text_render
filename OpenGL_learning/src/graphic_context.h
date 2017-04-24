#pragma  once
#include "stdafx.h"

DrawContext* GraphicContext_construct(int width,int height)	;

DrawContext* getGraphicContext();

void Graphic_destruct();

void setGraphicCallbackCollections();

