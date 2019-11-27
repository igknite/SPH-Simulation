#include"Simulator.h"

Simulator::Simulator()
{
	timsStep = 0.001f;
	mySPH = new SPH(1000);	// the number of particles
}
Simulator::~Simulator()
{

}

void Simulator::Initialize()
{
	timsStep = 0.006;
	mySPH->iteration_n = 6;
	mySPH->init();
}

void Simulator::Update()
{
	vec2 gravity(0.0, -9.8 / mySPH->iteration_n);
	
	//Update
	for (int iter = 0; iter < mySPH->iteration_n; iter++)
	{
		mySPH->update(timsStep, gravity);
	}
}

void Simulator::Render()
{
	mySPH->draw();
}

