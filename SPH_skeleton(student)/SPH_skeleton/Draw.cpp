#include "Particle.h"
#include <GL/glut.h>

void Particle::draw()
{
	glColor3f(0.0f, 0.1f, 0.2f);
	glPointSize(2.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2f(getPosX(), getPosY());
	glEnd();
}