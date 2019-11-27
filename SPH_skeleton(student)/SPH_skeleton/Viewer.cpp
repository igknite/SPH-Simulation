#pragma once
#include <iostream>
#include "Viewer.h"
#include "Windows.h"
using namespace std;

Viewer::Viewer(void)
{
	m_start = false;
}

Viewer::~Viewer(void)
{
}

void Viewer::Initialize(void)
{
	S_Simulator.Initialize();
}

void Viewer::Update()
{
	if (m_start == true)
	{
		S_Simulator.Update();
	}
}

void Viewer::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	S_Simulator.Render();

	glutSwapBuffers();
}

void Viewer::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, 0, 100);
	//glOrtho(-20.5, 20.5, -20.5, 20.5, 0, 100);
	glutPostRedisplay();
}

void Viewer::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
	case 'Q':
		exit(0);
		break;
	case' ':
		m_start = !m_start;
		break;
	case 'r':
	case 'R':
		S_Simulator.Initialize();
		break;
	}
	glutPostRedisplay();
}
