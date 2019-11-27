#pragma once   
#include <iostream>
#include <GL/glut.h>
#include "SPH.h"

using namespace std;


class Simulator
{
public:
	Simulator(void);
	~Simulator(void);

public:
	void					Initialize();
	void					Update();
	void					Render();

public:
	SPH						*mySPH;
	double					timsStep;
};

