/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include <math.h>
std::random_device rd1;
std::mt19937 rng1(rd1());


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	p(gfx, {0,191,255})
{
	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		for (int i = 0; i < p.no_of_particles; i++) {
			p.p[i].side++;
			}
	}
	if (wnd.kbd.KeyIsPressed(VK_BACK)) {

		for (int i = 0; i < p.no_of_particles; i++) {
			p.p[i].side--;
		}
	}
	if (wnd.mouse.LeftIsPressed()) {
		p.attract_to({ (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() });
	}
	for (int i = 0; i < p.no_of_particles; i++) {
		Adjust_particle_x(p.p[i]);
		Adjust_particle_y(p.p[i]);
		p.p[i].loc.x += p.p[i].vx;
		p.p[i].vy = (float)50 * cos(0.05*p.p[i].loc.x)*0.05*p.p[i].vx;
		p.p[i].loc.y += p.p[i].vy;
		
	}
}
void Game::Adjust_particle_x(Particle &p)
{
	std::uniform_real_distribution <float> x(1,3);
	std::uniform_int_distribution <int> y(2, 10);
	std::uniform_real_distribution <float> y1(0.03, 0.05);
	if ((p.loc.x + p.side) >= 750) {

		p.loc.x = (750 - p.side);
		p.vx = -x(rng1);
	//	p.vy = -y(rng1) * 10 * cos((float)p.loc.x*y1(rng1))*y1(rng1)*p.vx;
	}
	else if (p.loc.x <= 50) {
		p.loc.x = 50;
		p.vx = x(rng1);
		//p.vy = y(rng1) * 10 * cos((float)p.loc.x*y1(rng1))*y1(rng1)*p.vx;
	}
}
void Game::Adjust_particle_y(Particle & p)
{
	std::uniform_int_distribution <int> y(2, 10);
	std::uniform_real_distribution <float> y1(0.03, 0.05);
	if ((p.loc.y + p.side) >= 550) {
		p.loc.y = 550 - p.side;
		p.vy = -y(rng1)*10 * cos((float)p.loc.x*y1(rng1))*y1(rng1)*p.vx;
	}
	else if (p.loc.y <= 50) {
		p.loc.y = 50;
		p.vy = y(rng1)*10 * cos((float)p.loc.x*y1(rng1))*y1(rng1)*p.vx;
	}
}
void Game::Draw_Border()
{
	for (int a = 50; a <= 750; a++) {
		gfx.PutPixel(a, 50, 255, 255, 255);
	}
	for (int b = 50; b <= 750; b++) {
		gfx.PutPixel(b, 550, 255, 255, 255);
	}
	for (int c = 50; c <= 550; c++) {
		gfx.PutPixel(50, c, 255, 255, 255);
	}
	for (int d = 50; d <= 550; d++) {
		gfx.PutPixel(750, d, 255, 255, 255);
	}

}
void Game::ComposeFrame()
{
	Draw_Border();
	p.draw(p.c);
}
