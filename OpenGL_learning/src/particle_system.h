#pragma once

#include "stdafx.h"
#include "graphic_context.h"

struct Particle
{
	vec3f pos;
	Color color;
	float age;
	float radius;
	vec3f speed;
	vec3f acceleration;
	float life;
};

class ParticleSystem
{
public:
	ParticleSystem() {}

	ParticleSystem(int count, float gravity);

	~ParticleSystem();

	void init(); 

	void calculateAge(float dt); 

	void applyGravity();

	void render(int width, int height);

	void simulation(float dt);

	void particleMotion(float dt);

	void updateParticleStatus(int width, int height);
private:

	int m_count;
	float m_gravity;

	vector<Particle> m_particles;
	RsProgram* m_programe;
	GLuint m_centerLoc;
	GLuint m_radiusLoc;
	GLuint m_posLoc;
	GLuint m_colorLoc;
	GLuint m_sizeLoc;
	GLuint m_screenSizeLoc;

	GLuint m_vboRect;
	GLuint m_vboCenter;
	GLuint m_vao;

};

