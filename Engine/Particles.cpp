#include "Particles.h"
#include "Graphics.h"
#include "Colors.h"
#include <random>
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_real_distribution <float> xDist(50, 750);
std::uniform_real_distribution <float> yDist(50, 550);
//nice
void Particle::attract(Location n_loc)
{

		float x = n_loc.x;
		float y = n_loc.y;
		
		if (loc.x < x) {
			vx = 3;
		}
		else if (loc.x > (x+side)) {
			vx = -3;
		}
		else {
			vx = 0;
		};
		if (loc.y < y) {
			vy = 3;
		}
		else if (loc.y > (y+side)) {
			vy = -3;
		}
		else {
			vy = 0;
		};
}
void Particles::trail() {

}
Particle::Particle()
{
	loc.x = 100;
	loc.y = 300;
	vx = 3;
	vy = 50*cos(0.05*loc.x)*0.05*vx;
}

Particles::Particles(Graphics &gfx,Color c1) :
	gfxx(gfx)
{
	c = c1;
}


bool Particles::attract_to(Location loc) {
	

	for (int i = 0; i < no_of_particles; i++) {
		p[i].attract(loc);
	}
	return true;
}
void Particles::draw(Color c)
{
	for (int k = 0; k < no_of_particles; k++) {
		for (float i = p[k].loc.x; i < (p[k].side + p[k].loc.x); i++) {
			for (float j = p[k].loc.y; j < (p[k].side + p[k].loc.y); j++) {
				gfxx.PutPixel((int)i, (int)j, c);
			}
		}
	}
}


