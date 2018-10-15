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
	p(gfx, { 0,191,255 }),
	p1(gfx, Colors::Green),
	p2(gfx, Colors::Yellow)
{
	p1.vx = 1;
	p1.loc.x = 300;
	p1.loc.y = (p1.loc.x - 300)*(p1.loc.x - 300) + 300;

	p2.vx = 2;
	p2.loc.x = 50;
	p2.loc.y =  50*(2*cos(0.01*p2.loc.x) + (sin(0.04*p2.loc.x)*sin(0.04*p2.loc.x)) )+275;
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
		p.side++;
		p1.side++;
		p2.side++;
	}
	if (wnd.kbd.KeyIsPressed(VK_BACK)) {
		p.side--;
		p1.side--;
		p2.side--;
	}
	Adjust_particle(p);
	Adjust_parabola(p1);
	Adjust_particle(p2);

	p.loc.x += p.vx;
	p1.loc.x += p1.vx;
	p2.loc.x += p2.vx;
	
	p.vy = (float)50 * cos(0.05*p.loc.x)*0.05*p.vx; //differentiated sin function
	p1.vy = (float)-(2 * (p1.loc.x - 300) * p1.vx) / 10;//differentiated parabola 
	p2.vy = (float)50 * ((sin(0.08*p2.loc.x)*0.04) - (2 * sin(0.01*p2.loc.x)*0.01))*p2.vx;
	
	p.loc.y += p.vy;
	p1.loc.y += p1.vy;
	p2.loc.y += p2.vy;
}
void Game::Adjust_parabola(Particle &p1) {

	if ((p1.loc.y + p1.side) >= 550) {
		p1.loc.y = 550 - p1.side;
		p1.vy = -p1.vy;
		p1.vx = -p1.vx;
	}
	else if (p1.loc.y <= 50) {
		p1.loc.y = 50;
		p1.vy = -p1.vy;
		p1.vx = -p1.vx;
	}
	else {};
}
void Game::Adjust_particle_x(Particle &p)
{
	if ((p.loc.x + p.side) >= 750) {

		p.loc.x = (750 - p.side);
		p.vx = -p.vx;
	}
	else if (p.loc.x <= 50) {
		p.loc.x = 50;
		p.vx = -p.vx;
	}
}
void Game::Adjust_particle_y(Particle & p)
{
	if ((p.loc.y + p.side) >= 550) {
		p.loc.y = 550 - p.side;
		p.vy = -p.vy;
	}
	else if (p.loc.y <= 50) {
		p.loc.y = 50;
		p.vy = -p.vy;
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
void Game::Adjust_particle(Particle & p)
{
	Adjust_particle_x(p);
	Adjust_particle_y(p);
}

void Game::ComposeFrame()
{
	Draw_Border();
	p.draw();
	p1.draw();
	p2.draw();
}
