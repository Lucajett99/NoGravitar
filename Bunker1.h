#pragma once
typedef class Bullets* ptr_Bullets;
typedef class PlanetSurface* ptr_PlanetSurface;
typedef class Spaceship* ptr_Spaceship;

typedef class Bunker1* ptr_Bunker1;
struct listaBunker1 {
	Bunker1* b1;
	listaBunker1* next;
};
typedef listaBunker1* ptr_listaBunker1;


class Bunker1 {
protected:
	int xBunker1;
	int yBunker1;
	int lifeBunker1;
	ptr_Bullets SX;
	ptr_Bullets DX;
public:
	Bunker1(int x, int y, int life);
	int coordinateBunker1(bool b);
	void minusLife();
	int returnLife();
	void addSpari(int x, int y);
	void refreshSpari(Spaceship& p, ptr_PlanetSurface planet);
};
typedef class Bunker1* ptr_Bunker1;

