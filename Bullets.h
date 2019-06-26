#pragma once
#include <iostream>
#include "Bunker1.h"
#include "Bunker2.h"

typedef class Spaceship* ptr_Spaceship;
typedef class PlanetSurface* ptr_PlanetSurface;

struct BulletsList {
	int xBullet;
	int yBullet;
	bool eliminato;
	BulletsList* next;
};
typedef BulletsList* ptr_BulletsList;



class Bullets {
protected:
	ptr_BulletsList head;

public:
	Bullets();
	void addBullets(int x, int y);
	ptr_BulletsList deleteBullets(ptr_BulletsList tmp);
	void refresh(Spaceship& p,ptr_PlanetSurface planet, int Xinc, int Yinc);
	ptr_listaBunker1 modificaLista1(ptr_listaBunker1 &head, int x, int y, ptr_PlanetSurface planet);
	ptr_listaBunker2 modificaLista2(ptr_listaBunker2 &head, int x, int y, ptr_PlanetSurface planet);

	ptr_BulletsList returnList();
	void setList(ptr_BulletsList p);
};
typedef class Bullets* ptr_Bullets;