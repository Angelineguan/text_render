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

	void render();

	void simulation(float dt);

	void particleMotion(float dt);


private:

	int m_count;
	float m_gravity;

	vector<Particle> m_particles;
	vec3f* m_points;

	RsProgram* m_programe;
	GLuint m_particleCenterLoc;
	GLuint m_particleColorLoc;
	GLuint m_particleRadiusLoc;
	GLuint m_particleAgeLoc;

	GLuint m_vbo;
	GLuint m_vao;
};

