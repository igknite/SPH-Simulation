#include "Particle.h"
#include <GL/glut.h>

void Particle::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(2.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2f(getPosX(), getPosY());
	glEnd();
}