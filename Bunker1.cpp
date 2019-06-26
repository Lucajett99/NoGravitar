#include <iostream>
#include "Bunker1.h"
#include "Bullets.h"
using namespace std;


Bunker1::Bunker1(int x, int y, int life) {
	xBunker1 = x;
	yBunker1 = y;
	lifeBunker1 = life;
	SX = new Bullets();
	DX = new Bullets();
}


int Bunker1::coordinateBunker1(bool b) {
	if (b) return xBunker1;
	else return yBunker1;
}

void Bunker1::minusLife() {
	lifeBunker1--;
}

int Bunker1::returnLife() {
	return lifeBunker1;
}

void Bunker1::addSpari(int x, int y) {
	SX->addBullets(x, y);
	DX->addBullets(x, y);
}

void Bunker1::refreshSpari(Spaceship& p, ptr_PlanetSurface planet) {
	SX->refresh(p, planet, -1, -1);
	DX->refresh(p, planet, 1,-1);
}
