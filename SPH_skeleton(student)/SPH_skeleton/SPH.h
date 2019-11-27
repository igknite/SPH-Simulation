#pragma once
#include "Particle.h"

using namespace std;
#define SPH_PI 3.1415926
#define GRIDSIZE 40

class SPH
{
public:
	vector<Particle *> particles;
	int index;				//particle index
	int MaxParticle;
	int iteration_n;
private:
	double rest_density;	// rest density
	double mu;				// viscosity constant
	double h;				// kernel radius
	double k;				// gas constant
	
public:
	SPH();
	SPH(int numparticle);
	~SPH();
	
	void resetParticle();
	void init();
	void damBreaking();
	void pouring();
	void update(float dt, vec2 gravity);
	void draw();
	void makeHashTable();
	void computeDensity();
	void computeForce();
	void integrate(double dt, vec2 gravity);

private:	//kernel functions for SPH
	double	poly6Kernel(vec2 rij, double h);
	vec2	spikygradientKernel(vec2 rij, double q);
	double	viscositylaplacianKernel(vec2 rij, double q);
private:
	vector<Particle *> hashGrid[GRIDSIZE][GRIDSIZE];
	vector<Particle *> getNeighbor(int gridx, int gridy, double radius, vector<Particle *>& mine);
};