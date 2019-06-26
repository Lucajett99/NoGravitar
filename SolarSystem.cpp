#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "SolarSystem.h"
using namespace std;


SolarSystem::SolarSystem(Spaceship p) {
	srand((unsigned)time(0));
	int numberPlanets = ((rand() % 3) + 4);
	ptr_SS tmp = new SS();
	tmp->numberSolarSystem = 1;
	tmp->puntatore_planet = creaListaPianeti(p, tmp->puntatore_planet, numberPlanets);
	tmp->completed = false;
	tmp->next = NULL;
	tmp->prev = NULL;
	SSystem = tmp;
	tmp = NULL;
	delete tmp;
}


void SolarSystem::addSolarSystem(Spaceship p) {
	srand((unsigned)time(0));
	int numberPlanets = ((rand() % 3) + 4);
	if (SSystem->next == NULL) {
		ptr_SS tmp = new SS();
		tmp->numberSolarSystem = 2;
		tmp->puntatore_planet = creaListaPianeti(p, tmp->puntatore_planet, numberPlanets);
		tmp->completed = false;
		tmp->next = NULL;
		tmp->prev = SSystem;
		SSystem->next = tmp;
		tmp = NULL;
		delete tmp;
	}
	else {
		int i = 3;
		ptr_SS tmp, tmpNew, tmpOld;
		tmpOld = SSystem;
		tmpNew = SSystem->next;
		while (tmpOld->next->next != NULL) {
			tmpOld = tmpNew;
			tmpNew = tmpNew->next;
			i++;
		}
		tmp = new SS();
		tmp->numberSolarSystem = i;
		tmp->puntatore_planet = creaListaPianeti(p, tmp->puntatore_planet, numberPlanets);
		tmp->completed = false;
		tmp->next = NULL;
		tmp->prev = tmpNew;
		tmpNew->next = tmp;
		tmp = NULL;
		tmpNew = NULL;
		tmpOld = NULL;
		delete tmp;
		delete tmpNew;
		delete tmpOld;
	}
}


ptr_Planet SolarSystem::creaListaPianeti(Spaceship p, ptr_Planet head, int numberPlanets) {
	for (int i = 1; i <= numberPlanets; i++) {
		int xPlanet = ((rand() % 8) + 5);
		int yPlanet = ((rand() % 12) + 2);
		if ((xPlanet == 3) && (yPlanet == 3)) {
			xPlanet++;
			yPlanet++;
		}
		if (head == NULL) {
			ptr_Planet tmp;
			tmp = new Planet();
			tmp->numberPlanet = i;
			tmp->xPlanet = xPlanet;
			tmp->yPlanet = yPlanet;
			tmp->listBunker1 = NULL;
			tmp->listBunker2 = NULL;
			tmp->planetSurface = new PlanetSurface(p, tmp->listBunker1, tmp->listBunker2);
			tmp->next = NULL;
			tmp->prev = NULL;
			head = tmp;
		}
		else if (head->next == NULL) {
			ptr_Planet tmp;
			tmp = new Planet();
			tmp->numberPlanet = i;
			tmp->xPlanet = xPlanet;
			tmp->yPlanet = yPlanet;
			tmp->listBunker1 = NULL;
			tmp->listBunker2 = NULL;
			tmp->planetSurface = new PlanetSurface(p, tmp->listBunker1, tmp->listBunker2);
			tmp->next = NULL;
			tmp->prev = head;
			head->next = tmp;
			tmp = NULL;
			delete tmp;
		}
		else {
			ptr_Planet tmpOld, tmpNew;
			tmpOld = head;
			tmpNew = head->next;
			while (tmpOld->next->next != NULL) {
				tmpOld = tmpNew;
				tmpNew = tmpNew->next;
			}
			ptr_Planet tmp;
			tmp = new Planet();
			tmp->numberPlanet = i;
			tmp->xPlanet = xPlanet;
			tmp->yPlanet = yPlanet;
			tmp->listBunker1 = NULL;
			tmp->listBunker2 = NULL;
			tmp->planetSurface = new PlanetSurface(p, tmp->listBunker1, tmp->listBunker2);
			tmp->next = NULL;
			tmp->prev = tmpNew;
			tmpNew->next = tmp;
			tmp = NULL;
			tmpNew = NULL;
			tmpOld = NULL;
			delete tmp;
			delete tmpNew;
			delete tmpOld;
		}
	}
	return head;
}


void SolarSystem::setMappUniverso(Spaceship p) {
	if (returnIfDestroyed()) addSolarSystem(p);
	Mapp::setMapp();    //setta la cornice
	setSolarSystemParameters(p.returnParameter(100), p.returnParameter(10), SSystem->numberSolarSystem);
	matrice[p.returnParameter(1)][p.returnParameter(2)] = 'Y';

	if (SSystem->completed) {
		matrice[90][5] = 'C';
		matrice[91][5] = 'O';
		matrice[92][5] = 'M';
		matrice[93][5] = 'P';
		matrice[94][5] = 'L';
		matrice[95][5] = 'E';
		matrice[96][5] = 'T';
		matrice[97][5] = 'A';
		matrice[98][5] = 'T';
		matrice[99][5] = 'O';
	}

	ptr_Planet tmp = SSystem->puntatore_planet;
	//setta 'O' per rappresentare i Pianeti in base alle loro coordinate
	while (tmp != NULL) {
		if ((tmp->listBunker1 == NULL) && (tmp->listBunker2 == NULL)) matrice[tmp->xPlanet][tmp->yPlanet] = 'X';
		else  matrice[tmp->xPlanet][tmp->yPlanet] = 'O';
		tmp = tmp->next;
	}
}


void SolarSystem::spostamentoUniverso(char& moveSpaceshipUniverso) {
	if (GetAsyncKeyState(VK_UP)) moveSpaceshipUniverso = 72;
	else if (GetAsyncKeyState(VK_LEFT)) moveSpaceshipUniverso = 75;
	else if (GetAsyncKeyState(VK_RIGHT)) moveSpaceshipUniverso = 77;
	else if (GetAsyncKeyState(VK_DOWN)) moveSpaceshipUniverso = 80;
	else if (GetAsyncKeyState(0x51)) moveSpaceshipUniverso = '2';
	else if (GetAsyncKeyState(' ')) moveSpaceshipUniverso = '2';

}


char SolarSystem::interationSpaceship(Spaceship & p, bool& b, int& numeroSS) {
	char n;
	spostamentoUniverso(n);
	if (n == 75) {
		if (!b) {
			if (matrice[p.returnParameter(1) - 1][p.returnParameter(2)] == ' ') p.moveSpaceshipSolarSystem(n);
			else if (p.returnParameter(1) > 1) b = true;
			else if ((SSystem->prev != NULL) && (SSystem->prev->completed)) {
				numeroSS--;
				p.modificaCoordinateInCasoDiNuovoSistemaSolare(1);
			}
		}
	}
	else if (n == 77) {
		if (!b) {
			if (matrice[p.returnParameter(1) + 1][p.returnParameter(2)] == ' ') p.moveSpaceshipSolarSystem(n);
			else if (p.returnParameter(1) < 77) b = true;
			else if ((SSystem->next != NULL) && (SSystem->completed)) {
				numeroSS++;
				p.modificaCoordinateInCasoDiNuovoSistemaSolare(0);
			}
		}
	}
	else if (n == 72) {
		if (!b) {
			if (matrice[p.returnParameter(1)][p.returnParameter(2) - 1] == ' ')  p.moveSpaceshipSolarSystem(n);
			else if (p.returnParameter(2) > 1) b = true;
		}
	}
	else if (n == 80) {
		if (!b) {
			if (matrice[p.returnParameter(1)][p.returnParameter(2) + 1] == ' ') p.moveSpaceshipSolarSystem(n);
			else if (p.returnParameter(2) < 19) b = true;
		}
	}
	return n;
}



ptr_PlanetSurface SolarSystem::pianetaCor(Spaceship p, char n) {
	ptr_Planet tmp = SSystem->puntatore_planet;
	int xPos = p.returnParameter(1);
	int yPos = p.returnParameter(2);
	if (n == 77) xPos++;
	else if (n == 75) xPos--;
	else if (n == 72) yPos--;
	else if (n == 80) yPos++;
	while ((tmp->xPlanet != xPos) || (tmp->yPlanet != yPos)) {
		tmp = tmp->next;
	}
	return tmp->planetSurface;
}

void SolarSystem::xxx(Spaceship p, char n, ptr_listaBunker1 head1, ptr_listaBunker2 head2) {
	ptr_Planet tmp = SSystem->puntatore_planet;
	int xPos = p.returnParameter(1);
	int yPos = p.returnParameter(2);
	if (n == 77) xPos++;
	else if (n == 75) xPos--;
	else if (n == 72) yPos--;
	else if (n == 80) yPos++;
	while ((tmp->xPlanet != xPos) || (tmp->yPlanet != yPos)) {
		tmp = tmp->next;
	}
	tmp->listBunker1 = head1;
	tmp->listBunker2 = head2;
}


void SolarSystem::solarSystemDestroyed() {
	int i = 0;
	ptr_Planet tmp = SSystem->puntatore_planet;
	while (tmp != NULL) {
		if ((tmp->listBunker1 != NULL) && (tmp->listBunker2 != NULL)) i = 1;
		else if ((tmp->listBunker1 != NULL) || (tmp->listBunker2 != NULL)) i = 1;
		tmp = tmp->next;
	}
	if (i == 0) SSystem->completed = true;
}


void SolarSystem::solarSystemChange(int i) {
	while (SSystem->numberSolarSystem != i) {
		if (i < SSystem->numberSolarSystem)        SSystem = SSystem->prev;
		else if (i > SSystem->numberSolarSystem)   SSystem = SSystem->next;
	}
	solarSystemDestroyed();
	SSystem->completed = returnIfDestroyed();
}


bool SolarSystem::returnIfDestroyed() {
	return SSystem->completed;
}