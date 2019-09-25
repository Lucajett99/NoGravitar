#pragma once


struct Bullet {
	int xBullet;      //coordinata x del proiettile
	int yBullet;      //coordinata y del proiettile
	bool eliminato;   //ci serve per vedere se eliminarlo o meno
	Bullet* next;     //puntatore al proiettile successivo
};
typedef Bullet* ptr_Bullet;

class BulletsList {
protected:
	ptr_Bullet listaProiettili;
public:
	BulletsList();
	void addBullets(int x, int y, bool b);
	void deleteBullets();
	ptr_Bullet retrunList();
};
typedef class BulletsList* ptr_BulletsList;