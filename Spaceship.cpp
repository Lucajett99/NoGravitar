#include <conio.h>
#include <iostream>
#include "Spaceship.h"

using namespace std;

//crea la navicella e setta la sua posizione iniziale 
Spaceship::Spaceship() {
	setMapp();
	p1 = 3;
	p2 = 3;
	p3 = 3;
	p4 = 3;
	life = 5;
	fuel = 1000;
	LP = new Bullets();
}


//modifica la nuova posizione della navicella del sistema solare
//prima di modificare le coordinate della navicella, fa un controllo per evitare che esca dalla mappa
void Spaceship::moveSpaceshipSolarSystem(char n) {
	if ((matrice[p1 - 1][p2] == ' ') && n == 75)           p1 = p1 - 1;			//SINISTRA---controllo margine
	else if ((matrice[p1 + 1][p2] == ' ') && n == 77)      p1 = p1 + 1;        	//DESTRA---controllo margine
	else if ((matrice[p1][p2 - 1] == ' ') && n == 72)	   p2 = p2 - 1;	        //SU---controllo marigine
	else if ((matrice[p1][p2 + 1] == ' ') && n == 80)	   p2 = p2 + 1;            //GIU---controllo margine
}


//modifica la nuova posizione della navicella del sistema solare
//prima di modificare le coordinate della navicella, fa un controllo per evitare che esca dalla mappa
void Spaceship::moveSpaceshipPlanet(char n) {
	if ((matrice[p3 - 1][p4] == ' ') && n == 75)           p3 = p3 - 1;			//SINISTRA---controllo margine
	else if ((matrice[p3 + 1][p4] == ' ') && n == 77)      p3 = p3 + 1;        	//DESTRA---controllo margine
	else if (n == 72)	                                   p4 = p4 - 1;	         //SU---controllo marigine
	else if ((matrice[p3][p4] == ' ') && n == 80)	       p4 = p4 + 1;         //GIU---controllo margine
}


int Spaceship::returnParameter(int i) {
	if (i == 1) return p1;
	else if (i == 2) return p2;
	else if (i == 3) return p3;
	else if (i == 4) return p4;
	else if (i == 10) return life;
	else if (i == 100) return fuel;
}


void Spaceship::fuelMinus() {
	fuel--;
}


void Spaceship::lifeMinus() {
	life--;
}


void Spaceship::setInitialPosition() {
	p3 = 3;
	p4 = 3;
}


void Spaceship::fuelPlus(int i) {
	if (i == 0) fuel = fuel + 500;
	else if (i == 1) fuel = fuel + 100;
}


bool Spaceship::spaceshipIsAlive() {
	if ((fuel >= 1) && (life >= 1)) return true;
	else return false;
}


void Spaceship::modificaCoordinateInCasoDiNuovoSistemaSolare(int i) {
	if (i == 0) p1 = 1;
	else if (i == 1) p1 = 77;
}

ptr_Bullets Spaceship::returnP() {
	return LP;
}