#pragma once
#include "Mouse.h"
#include "Graphics.h"
class Location {
public:
	float x, y;
	void add(float dx, float dy){
		x += (int)dx;
		y += (int)dy;
	}
};
class Particle
{
public:
	void attract(Location n_loc);
	float side=10;
	Location loc;
	float vx=1, vy=1;
	Particle();
};
class Particles {

public:	
	int no_of_particles=1;
	Particles(Graphics &gfx, Color c1);
	Color c;
	Graphics &gfxx;
	Particle p[1];
	void draw(Color c);
	void trail();
	bool attract_to(Location loc);
};

