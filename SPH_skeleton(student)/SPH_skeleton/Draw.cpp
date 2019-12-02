#include "Particle.h"
#include <GL/glut.h>

void Particle::draw()
{
	//glColor3f(0.0f, 0.1f, 0.2f);
	glColor3f(color.x,color.y,color.z);
	glPointSize(2.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex3f(getPosX(), getPosY(),getPosZ());
	glEnd();
}