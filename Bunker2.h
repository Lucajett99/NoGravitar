#pragma once

#include "BulletsList.h"

typedef class Bunker2* ptr_Bunker2;
struct listaBunker2 {
	Bunker2* b2;
	listaBunker2* next;
};
typedef listaBunker2* ptr_listaBunker2;


class Bunker2 {
protected:
	int xBunker2;
	int yBunker2;
	int lifeBunker2;
	ptr_BulletsList LPsx;
	ptr_BulletsList LPdx;
	ptr_BulletsList LPcentrale;
public:
	Bunker2(int x, int y, int life);
	int coordinateBunker2(bool b);
	void minusLife();
	int returnLife();
	void addBulletSBunker2();
	void deleteBulletSBunker2();
	void deleteAllBulletsBunker2();
	ptr_BulletsList returnLP(int n);
};
typedef class Bunker2* ptr_Bunker2;
