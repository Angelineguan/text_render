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

struct Point
{
	vec3f center;
	Color color;
	float radius;
};

class ParticleSystem
{
public:
	ParticleSystem(int count, float gravity);

	~ParticleSystem();

	void render(int width, int height);

private:
	void init(); 

	void updateParticleStatus(int width, int height);
	void particleMotion(float dt);
	void calculateAge(float dt);
	void applyGravity();
	void simulation(float dt);

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
