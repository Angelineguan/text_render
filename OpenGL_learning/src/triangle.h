#pragma  once
#include "stdafx.h"
#include "rs_programe.h"

class Triangle 
{
public:
	Triangle(GLfloat* vertex, size_t num);
	~Triangle();

	virtual void draw();
	void setIsDrawOutline(bool isDrawOutline) {
		m_isDrawOutline = isDrawOutline;
	}
	void setInnerColor(Color color);
	void setOutLineColor(Color color);
	void setOffset(vec3f* offset);
private:
	RsProgram* m_programe;
	GLuint m_vboHandle;
	GLuint m_vaoHandle;
	Color m_innerColor;
	Color m_outLineColor;
	vec3f m_offset;
	bool m_isDrawOutline;
};
