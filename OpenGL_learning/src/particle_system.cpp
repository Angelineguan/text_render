#include "particle_system.h"
#include <time.h>


GLfloat vertex11[] = {
	-0.5f, -0.5f, -0.5,
	0.5f, -0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0,  0.5f,  -0.5,
	0.5f, -0.5f,  -0.5,
	1.0f, 0.5f,  -0.5
};

ParticleSystem::ParticleSystem(int count, float gravity) : m_count(count), m_gravity(gravity)
{
	init();

	m_programe = GraphicContext::instance()->getParticleProgrameInstance();

	m_particleCenterLoc = m_programe->getAttributeLoc("inParticleCenter");
	m_particleAgeLoc = m_programe->getAttributeLoc("inParticleAge");
	m_particleColorLoc = m_programe->getAttributeLoc("inParticleColor");
	m_particleRadiusLoc = m_programe->getAttributeLoc("inParticleRadius");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(vec3f), m_points, GL_STATIC_DRAW);

	glVertexAttribPointer(m_particleCenterLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)2);
	glEnableVertexAttribArray(m_particleCenterLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//glGenVertexArrays(1, &m_vao);
	//glBindVertexArray(m_vao);

	//glGenBuffers(1, &m_vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Particle), &m_particles[0], GL_DYNAMIC_DRAW);

	//glEnableVertexAttribArray(m_particleCenterLoc);
	//glVertexAttribPointer(m_particleCenterLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);

	//glEnableVertexAttribArray(m_particleColorLoc);
	//glVertexAttribPointer(m_particleColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)3);

	//glEnableVertexAttribArray(m_particleAgeLoc);
	//glVertexAttribPointer(m_particleAgeLoc, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)7);

	//glEnableVertexAttribArray(m_particleRadiusLoc);
	//glVertexAttribPointer(m_particleRadiusLoc, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)8);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void ParticleSystem::init()
{
	srand(unsigned(time(0)));

	Color colors[3] = { {0,0,1,1}, {1,0,1,1} };

	for (int i = 0; i< m_count;i++)
	{
		Particle temp = { 
			vec3f(0,0,0),
			colors[rand() % 2],
			0.0f,
			0.3f,
			vec3f((rand() % 50) - 26.0f,(rand() % 50) - 26.0f, (rand() % 50) - 26.0f),
			vec3f(0,0,0),
			0.5f + 0.05f * (rand() % 10)
		};
		m_particles.push_back(temp);
	}

	m_points = new vec3f[m_count];
	for (int i = 0; i < m_count; i++)
	{

		vec3f point = vec3f((rand() % 100), (rand() % 100), 0) * 0.01f;
		m_points[i] = point;
	}
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_points;
}


void ParticleSystem::simulation(float dt)
{
	calculateAge(dt);
	applyGravity();
	particleMotion(dt);
}

void ParticleSystem::calculateAge(float dt)
{
	for (vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end();itr++)
	{
		itr->age += dt;

		if (itr->age > itr->life)
		{
			itr->pos = vec3f(0, 0, 0);
			itr->age = 0;
			itr->speed = vec3f((rand() % 30 - 15.0f), (rand() % 30 - 11.0f), (rand() % 30 - 15.0f));
		}
	}
}

void ParticleSystem::applyGravity()
{
	for (vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end(); itr++)
	{
		itr->acceleration = vec3f(0, m_gravity, 0);
	}
}

void ParticleSystem::particleMotion(float dt)
{
	for (vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end(); itr++)
	{
		itr->pos = itr->pos + itr->speed * dt;
		itr->speed = itr->speed + itr->acceleration * dt;
	}
}
 
void ParticleSystem::render()
{
	m_programe->usePrograme();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(m_vao);

	glDrawArrays(GL_TRIANGLES, 0,9);
	
	glBindVertexArray(0);
}

