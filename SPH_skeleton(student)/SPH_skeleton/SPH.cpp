#include "SPH.h"
#include <time.h>

SPH::SPH()
{

}

SPH::SPH(int numparticle)
{
	MaxParticle = numparticle;
	index = 0;	
	rest_density = 4.2;
	mu = 0.8;	
	h = 1.0;
	k = 50.0;
}

SPH::~SPH()
{
	while (!particles.empty())
	{
		particles.pop_back();
	}
	particles.clear();
}

void SPH::resetParticle()
{
	index = 0;
	while (!particles.empty())
	{
		particles.pop_back();
	}
}

void SPH::init()
{
	resetParticle();
	damBreaking();
}

void SPH::damBreaking()
{
	for (double y = -15.0; y < 20.0; y += 0.5) {
		for (double x = -18.0; x < -10.0; x += 0.5) {
			if (particles.size() < MaxParticle)
			{
				Particle *p = new Particle(x, y, index++);
				particles.push_back(p);
			}
		}
	}
	cout << "SPH" << particles.size() << " Paricles" << endl;
}

void SPH::pouring()
{
	if (particles.size() >= MaxParticle)
		return;

	for (double y = 10.0; y < 13.0; y += 0.4) {
		for (double x = -20.0; x < -20.0 + 3.0; x += 0.4) {
			if (particles.size() < MaxParticle)
			{
				Particle *p = new Particle(x, y, index++);
				p->velocity.x = 15.0f;
				particles.push_back(p);
			}
		}
	}
	cout << "SPH" << particles.size() << " Paricles" << endl;
}

void SPH::update(float dt, vec2 gravity)
{
	makeHashTable();
	computeDensity();
	computeForce();
	integrate(dt, gravity);
}

void SPH::draw()
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle *p = particles[i];
		p->draw();
	}
}

double SPH::poly6Kernel(vec2 rij, double h)
{
	double temp = 0.0;
	double norm = rij.dist();
	temp = h*h - norm * norm;

	return 4.0 / (SPH_PI*h*h*h*h*h*h*h*h) * temp*temp*temp;
}

vec2 SPH::spikygradientKernel(vec2 rij, double q)
{
	double temp = 0.0;
	temp = 1.0 - q*q;
	temp = -30.0 / (SPH_PI*h*h*h*h) * (temp*temp)/q;

	return  vec2(temp*rij.x, temp*rij.y);
}

double SPH::viscositylaplacianKernel(vec2 rij, double q)
{
	return 40.0 / (SPH_PI*h*h*h*h) * (1.0 - q);
}

void SPH::computeDensity()
{
	for (int x = 0; x < GRIDSIZE; x++)
	{
		for (int y = 0; y < GRIDSIZE; y++)
		{
			vector<Particle*> ris;
			vector<Particle*> rjs = getNeighbor(x, y, h, ris);

			for (int i = 0; i < ris.size(); i++)
			{
				Particle *pi = ris[i];
				pi->density = 0.0;	//compute with poly6Kernel
				
				/*Implements - Compute Density 작성, 아래 density 초기화는 지울 것*/
				pi->density = 1.0;
				
			}
		}
	}
}

void SPH::computeForce() // Compute Pressure and Viscosity
{
	for (int x = 0; x < GRIDSIZE; x++)
	{
		for (int y = 0; y < GRIDSIZE; y++)
		{
			vector<Particle*> ris;
			vector<Particle*> rjs = getNeighbor(x, y, h, ris);

			for (int i = 0; i < ris.size(); i++)
			{
				Particle *pi = ris[i];
				pi->fpressure = vec2(0.0, 0.0);//compute with spikygradientKernel
				pi->fviscosity = vec2(0.0, 0.0);//compute with viscositylaplacianKernel

				/*Implements - Compute Pressure and Viscosity Forces 작성*/

			}
		}
	}
}

void SPH::integrate(double dt, vec2 gravity)
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle *p = particles[i];
		p->integrate(dt, gravity);
	}
}

void SPH::makeHashTable()
{
	for (int p = 0; p < GRIDSIZE; p++)
	{
		for (int q = 0; q < GRIDSIZE; q++)
		{
			hashGrid[p][q].clear();
		}
	}
	
	for (int i = 0; i < particles.size(); i++)
	{
		Particle *p = particles[i];
		double x = (p->getPosX() + GRIDSIZE / 2);
		double y = (p->getPosY() + GRIDSIZE / 2);
		int gridx = (int)(x);					
		int gridy = (int)(y);					

		if (gridx < 0) gridx = 0;
		if (gridx > GRIDSIZE - 1) gridx = GRIDSIZE - 1;
		if (gridy < 0) gridy = 0;
		if (gridy > GRIDSIZE - 1) gridy = GRIDSIZE - 1;

		hashGrid[gridx][gridy].push_back(p);
	}
}

vector<Particle *> SPH::getNeighbor(int gridx, int gridy, double radius, vector<Particle*> &mine)
{
	vector<Particle *>res;
	mine.clear();
	for (int i = gridx - (int)radius; i <= gridx + (int)radius; i++)
	{
		for (int j = gridy - (int)radius; j <= gridy + (int)radius; j++)
		{
			if (i < 0 || i > GRIDSIZE - 1 || j < 0 || j > GRIDSIZE - 1)
				continue;

			for (int k = 0; k < hashGrid[i][j].size(); k++)
			{
				res.push_back(hashGrid[i][j][k]);

				if (i == gridx && j == gridy)
					mine.push_back(hashGrid[i][j][k]);
			}
		}
	}
	return res;
}
