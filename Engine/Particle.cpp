#include "Particle.h"
#include "Graphics.h"
#include "Colors.h"
#include <random>
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_real_distribution <float> xDist(50, 750);
std::uniform_real_distribution <float> yDist(50, 550);

Particle::Particle(Graphics &gfx, Color c1)
	: gfxx(gfx), c(c1)
{
	loc.x = 50;
	loc.y = 500;
	vx = 3;
	vy = 1;
}
void Particle::draw()
{
	for (float i = loc.x; i < (side + loc.x); i++) {
		for (float j = loc.y; j < (side + loc.y); j++) {
			gfxx.PutPixel((int)i, (int)j, c);
		}
	}
}



