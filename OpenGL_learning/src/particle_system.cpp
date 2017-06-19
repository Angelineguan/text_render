#include "particle_system.h"
#include <time.h>

vec3f points[] = {
	vec3f(-0.5f, -0.5f, -0.5), 
	vec3f(0.5f, -0.5f, -0.5),
	vec3f(0.5f, 0.5f, -0.5),
	vec3f(-0.5f, -0.5f, -0.5),
	vec3f(0.5f, 0.5f, -0.5),
	vec3f(-0.5f, 0.5f, -0.5),
};

ParticleSystem::ParticleSystem(int count, float gravity) : m_count(count), m_gravity(gravity)
{
	init();

	m_programe = GraphicContext::instance()->getParticleProgrameInstance();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vboRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboRect);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec3f), points, GL_STATIC_DRAW);

	m_posLoc= m_programe->getAttributeLoc("inPos");
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)0);
	glEnableVertexAttribArray(m_posLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_vboCenter);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboCenter);
	glBufferData(GL_ARRAY_BUFFER, m_count * m_count * sizeof(vec3f), m_centerPos, GL_STATIC_DRAW);

	m_centerLoc = m_programe->getAttributeLoc("inCenter");
	glVertexAttribPointer(m_centerLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)0);
	glEnableVertexAttribArray(m_centerLoc);
	glVertexAttribDivisor(m_centerLoc, 1);

//	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_vboColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboColor);
	glBufferData(GL_ARRAY_BUFFER, m_count * m_count * sizeof(vec4f), m_colors, GL_STATIC_DRAW);

	m_colorLoc = m_programe->getAttributeLoc("inColor");
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, GL_TRUE, sizeof(vec4f), (GLvoid*)0);
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribDivisor(m_colorLoc, 1);

	//m_sizeLoc = m_programe->getAttributeLoc("inSize");
	//glVertexAttribPointer(m_sizeLoc, 1, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)7);
	//glEnableVertexAttribArray(m_sizeLoc);
	//glVertexAttribDivisor(m_sizeLoc, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
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

	m_centerPos = new vec3f[m_count * m_count];
	for (int i = 0; i < m_count; i++)
	{
		for (int j = 0; j < m_count;j++)
		{
			vec3f point = vec3f(i * 0.08f, j * 0.08f, 0.0f);
			m_centerPos[i * m_count + j] = point;
		}
	}

	m_colors = new vec4f[m_count * m_count];
	for (int i = 0; i < m_count * m_count; i++)
	{
		m_colors[i] = vec4f(rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 256 / 256.0, 1.0f);
	}
}

ParticleSystem::~ParticleSystem()
{
	glDeleteBuffers(1, &m_vboRect);
	glDeleteBuffers(1, &m_vboCenter);
	glDeleteVertexArrays(1, &m_vao);
	delete[] m_centerPos;
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


	glBindVertexArray(m_vao);

//	m_programe->setUniform1f(m_radiusLoc,50.0f);
//	m_programe->setUniform3fv(m_centerLoc, vec3f(0, 0, 0));

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_count* m_count);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glBindVertexArray(0);
}

