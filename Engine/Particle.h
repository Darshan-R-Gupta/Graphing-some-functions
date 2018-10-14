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
	Location() {
		x = 0;
		y = 0;
	}
	Location(Location &loc) {
		x = loc.x;
		y = loc.y;
	}
};
class Particle
{
public:
	float side=10;
	Location loc;
	Graphics &gfxx;
	Color c;
	float vx=1, vy=1;
	Particle(Graphics &gfx, Color c1);
	void draw();
};

