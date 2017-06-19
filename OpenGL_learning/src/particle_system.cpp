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
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec3f), points, GL_STREAM_DRAW);

	m_posLoc= m_programe->getAttributeLoc("inPos");
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)0);
	glEnableVertexAttribArray(m_posLoc);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_vboCenter);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboCenter);
	glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Particle), &m_particles[0], GL_STREAM_DRAW);

	m_centerLoc = m_programe->getAttributeLoc("inCenter");
	glVertexAttribPointer(m_centerLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);
	glEnableVertexAttribArray(m_centerLoc);
	glVertexAttribDivisor(m_centerLoc, 1);

	m_colorLoc = m_programe->getAttributeLoc("inColor");
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, GL_TRUE, sizeof(Particle), (GLvoid*)(sizeof(vec3f)));
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribDivisor(m_colorLoc, 1);

	m_sizeLoc = m_programe->getAttributeLoc("inSize");
	glVertexAttribPointer(m_sizeLoc, 1, GL_FLOAT, GL_TRUE, sizeof(Particle), (GLvoid*)(sizeof(vec3f) + sizeof(Color) + sizeof(float)));
	glEnableVertexAttribArray(m_sizeLoc);
	glVertexAttribDivisor(m_sizeLoc, 1);


	m_screenSizeLoc = m_programe->getUniformLoc("screenSize");
	glUniform2f(m_screenSizeLoc, 800.0f, 800.0f);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ParticleSystem::init()
{
	srand(unsigned(time(0)));

	for (int i = 0; i< m_count;i++)
	{
		Particle temp = { 
			vec3f(((rand() % 50) - 26.0f) / 25.0f,((rand() % 50) - 26.0f) / 25.0f, ((rand() % 50) - 26.0f) / 25.0f),
		//	vec3f(0,0,0),
			Color(rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 10 /10.0f),
			0.0f,
			rand() % 30,
			vec3f(((rand() % 50) - 26.0f) / 25.0f,((rand() % 50) - 26.0f) / 25.0f, ((rand() % 50) - 26.0f) / 25.0f),
			vec3f(0,m_gravity,0),
			0.5f + 0.05f * (rand() % 10)
		};
		m_particles.push_back(temp);
	}

	m_centerPos = new Point[m_count * m_count];
	for (int i = 0; i < m_count; i++)
	{
		for (int j = 0; j < m_count;j++)
		{
			Point point;
			point.center= vec3f(i * 0.09f, j * 0.09f, 0.0f);
			point.color = Color(rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 10 / 10.0f);
			point.radius = rand() % 30;
			m_centerPos[i * m_count + j] = point;
		}
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
			itr->pos = vec3f(((rand() % 50) - 26.0f) / 25.0f, ((rand() % 50) - 26.0f) / 25.0f, ((rand() % 50) - 26.0f) / 25.0f);
			//itr->pos = vec3f(0, 0, 0);
			itr->age = 0;
			itr->speed = vec3f((rand() % 30 - 15.0f), (rand() % 30 - 11.0f), (rand() % 30 - 15.0f));
		}
	}
}

void ParticleSystem::applyGravity()
{
	for (vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end(); itr++)
	{
		itr->acceleration = vec3f(0, m_gravity, 0.5f * m_gravity);
	}
}

void ParticleSystem::particleMotion(float dt)
{
	for (vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end(); itr++)
	{
		itr->pos = itr->pos + itr->speed * dt ;
		itr->speed = itr->speed + itr->acceleration * dt;
	}
}

void ParticleSystem::render(int width, int height)
{
	m_programe->usePrograme();

	glBindVertexArray(m_vao);
	updateParticleStatus(width, height);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_count* m_count);
	glBindVertexArray(0);
}


void ParticleSystem::updateParticleStatus(int width, int height)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboRect);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec3f), points, GL_STATIC_DRAW);

	m_posLoc = m_programe->getAttributeLoc("inPos");
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (GLvoid*)0);
	glEnableVertexAttribArray(m_posLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboCenter);
	glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(Particle), &m_particles[0], GL_STATIC_DRAW);

	m_centerLoc = m_programe->getAttributeLoc("inCenter");
	glVertexAttribPointer(m_centerLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);
	glEnableVertexAttribArray(m_centerLoc);
	glVertexAttribDivisor(m_centerLoc, 1);

	m_colorLoc = m_programe->getAttributeLoc("inColor");
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, GL_TRUE, sizeof(Particle), (GLvoid*)(sizeof(vec3f)));
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribDivisor(m_colorLoc, 1);

	m_sizeLoc = m_programe->getAttributeLoc("inSize");
	glVertexAttribPointer(m_sizeLoc, 1, GL_FLOAT, GL_TRUE, sizeof(Particle), (GLvoid*)(sizeof(vec3f) + sizeof(Color) + sizeof(float)));
	glEnableVertexAttribArray(m_sizeLoc);
	glVertexAttribDivisor(m_sizeLoc, 1);

	glUniform2f(m_screenSizeLoc, (float)width, (float)height);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
