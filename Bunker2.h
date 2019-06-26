#pragma once
typedef class Bullets* ptr_Bullets;
typedef class Spaceship* ptr_Spaceship;
typedef class PlanetSurface* ptr_PlanetSurface;

typedef class Bunker2* ptr_Bunker2;
struct listaBunker2 {
	ptr_Bunker2 b2;
	listaBunker2* next;
	listaBunker2* prev;
};
typedef listaBunker2* ptr_listaBunker2;



class Bunker2 {
protected:
	int xBunker2;
	int yBunker2;
	int lifeBunker2;
	ptr_Bullets SX;
	ptr_Bullets CX;
	ptr_Bullets DX;
public:
	Bunker2(int x, int y, int life);
	int coordinateBunker2(bool b);
	void minusLife();
	int returnLife();
	void addSpari(int x, int y);
	void refreshSpari(Spaceship& p, ptr_PlanetSurface planet);
};
typedef class Bunker2* ptr_Bunker2;