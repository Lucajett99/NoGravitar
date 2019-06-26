#include <iostream>
#include "Bunker2.h"
#include "Bullets.h"
using namespace std;




Bunker2::Bunker2(int x, int y, int life) {
	xBunker2 = x;
	yBunker2 = y;
	lifeBunker2 = life;
	SX = new Bullets();
	CX = new Bullets();
	DX = new Bullets();
}


int Bunker2::coordinateBunker2(bool b) {
	if (b) return xBunker2;
	else return yBunker2;
}

void Bunker2::minusLife() {
	lifeBunker2--;
}

int Bunker2::returnLife() {
	return lifeBunker2;
}

void Bunker2::addSpari(int x, int y) {
	SX->addBullets(x, y);
	CX->addBullets(x, y);
	DX->addBullets(x, y);
}

void Bunker2::refreshSpari(Spaceship& p, ptr_PlanetSurface planet){
	SX->refresh(p, planet, -1, -1);
	CX->refresh(p, planet, 0, -1);
	DX->refresh(p, planet, 1, -1);
}