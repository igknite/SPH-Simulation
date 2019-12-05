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
	void					Lighting(void);
	void					DrawGround(void);
    float                   timer;
	int						t_inter;
	bool					on_HOS;
public:
	SPH						*mySPH;
	double					timsStep;
	vec3					ground;
};

