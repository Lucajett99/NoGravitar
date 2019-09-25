#pragma once
#include "Mapp.h"
#include "BulletsList.h"


class Spaceship : public Mapp {
protected:
	int p1;              //coordinate x della navicella nell'universo
	int p2;              //coordinate y della navicella nell'universo
	int p3;              //coordinate x della navicella all'interno del pianeta
	int p4;              //coordinate x della navicella all'interno del pianeta
	int life;	         //vita della navicella
	int fuel; 	         //carburante della navicella
	int score;           //punteggio della navicella 
	ptr_BulletsList LP;  //puntatore alla lista di proiettili 
public:
	Spaceship();
	void moveSpaceshipSolarSystem(char n);
	void moveSpaceshipPlanet(char n);
	int returnParameter(int i);
	void fuelMinus();
	void lifeMinus();
	void setScore(int i);
	void setInitialPosition();
	void fuelPlus(int i);
	bool spaceshipIsAlive();
	void modificaCoordinateInCasoDiNuovoSistemaSolare(int i);
	void addBulletSPaceship();
	void deleteBulletSPaceship();
	void deleteAllBulletsSpaceship();
	ptr_BulletsList returnLP();
};