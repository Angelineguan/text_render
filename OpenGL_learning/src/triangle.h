#pragma  once
#include "rs_programe.h"
#include "object.h"
#include "Vector3.h"
#include "util.h"

class Triangle : public Object
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
	void setOffset(vec3* offset);
private:
	GLuint m_vboHandle;
	GLuint m_vaoHandle;
	RsProgram* m_programe;
	Color m_innerColor;
	Color m_outLineColor;
	vec3 m_offset;
	Vector3 m_scale;
	bool m_isDrawOutline;
};
