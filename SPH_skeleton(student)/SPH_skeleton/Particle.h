#pragma once
#include <math.h>
#include <vector>
#include <algorithm>
#include "vector.h"
class Particle
{
public:
	double	mass;
	vec2	position;
	vec2	velocity;
	vec2	acceleration;
	double	density;
	int		idx;
	vec2	fpressure;
	vec2	fviscosity;
	double  restitution;
public:
	Particle(void)
	{
	}
	Particle(double _x, double _y)
	{
		position = vec2(_x, _y);
		velocity = vec2(0.0, 0.0);
		mass = 1.0;
		restitution = 0.5;
	}

	Particle(double _x, double _y, int _idx) : position(_x, _y), velocity(0.0, 0.0), acceleration(0.0, 0.0), mass(1.0)
	{
		fpressure = vec2(0.0, 0.0);
		fviscosity = vec2(0.0, 0.0);
		density = 0.0;
		idx = _idx;
		restitution = 0.5;
	}
	~Particle(void)
	{
	}

	double	getPosX(void) { return position.getX(); }
	double	getPosY(void) { return position.getY(); }

	void integrate(double dt, vec2 gravity)
	{
		vec2 fgrav = gravity * mass;

		// Update velocity and position
		acceleration = (fpressure + fviscosity) / density + fgrav;
		velocity = velocity + acceleration * dt;
		position = position + velocity * dt;

		// Boundary condition
		if (position.x < -20.0 && velocity.x < 0.0)
		{
			velocity.x *= -restitution;
			position.x = -20.0+0.1;
		}
		if (position.x > 20.0 && velocity.x > 0.0)
		{
			velocity.x *= -restitution;
			position.x = 20.0-0.1;
		}
		if (position.y < -20.0 && velocity.y < 0.0)
		{
			velocity.y *= -restitution;
			position.y = -20.0+0.1;
		}
		if (position.y > 20.0 && velocity.y > 0.0)
		{
			velocity.y *= -restitution;
			position.y = 20.0-0.1;
		}
	}

	void draw();
};
