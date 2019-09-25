#include <iostream>
#include "Bunker2.h"
using namespace std;



//assegna i valori all'oggetto Bunker2
Bunker2::Bunker2(int x, int y, int life) {
	xBunker2 = x;
	yBunker2 = y;
	lifeBunker2 = life;
	LPsx = new BulletsList();
	LPdx = new BulletsList();
	LPcentrale = new BulletsList();
}


//restituisce la posizione del Bunker2
int Bunker2::coordinateBunker2(bool b) {
	if (b) return xBunker2;
	else return yBunker2;
}


//toglie una vita al Bunker2 (nel caso venga colpito dal un "Bullet" della spaceship)
void Bunker2::minusLife() {
	lifeBunker2--;
}


//ritorna la vita del Bunker2
int Bunker2::returnLife() {
	return lifeBunker2;
}


//metodo per aggiungere dei "Bullet" a ciascuna delle tre liste di bullet che fanno parte del Bunker2
void Bunker2::addBulletSBunker2() {
	LPsx->addBullets(xBunker2, yBunker2, false);
	LPdx->addBullets(xBunker2, yBunker2, false);
	LPcentrale->addBullets(xBunker2, yBunker2, false);
}


//metodo per elminare i "Bullet" su ciascuna delle tre liste di bullet che fanno parte del Bunker2
void Bunker2::deleteBulletSBunker2() {
	LPsx->deleteBullets();
	LPdx->deleteBullets();
	LPcentrale->deleteBullets();
}


//metodo utilizzato per eliminare tutti i "Bullet" presenti nelle tre liste (viene ustao quando si esce dal pianeta)
//siccome il metodo deleteBullets() elimina solo i bullet in testa alla lista, viene ripetuto in un ciclo while finche la lista non si svuota
//viene eseguito il ciclo per ciascuna delle tre liste bullet del Bunker2
//prima un ciclo per assegnare a tutti i Bunker2 il valore true al campo "eliminato", e uno successivo per eliminarli dalla lista
void Bunker2::deleteAllBulletsBunker2() {
	ptr_Bullet tmpSx = LPsx->retrunList();
	while (tmpSx != NULL) {
		tmpSx->eliminato = true;
		tmpSx = tmpSx->next;
	}
	ptr_Bullet tmpCentrale = LPcentrale->retrunList();
	while (tmpCentrale != NULL) {
		tmpCentrale->eliminato = true;
		tmpCentrale = tmpCentrale->next;
	}
	ptr_Bullet tmpDx = LPdx->retrunList();
	while (tmpDx != NULL) {
		tmpDx->eliminato = true;
		tmpDx = tmpDx->next;
	}
	while (LPsx->retrunList() != NULL) LPsx->deleteBullets();
	while (LPcentrale->retrunList() != NULL) LPcentrale->deleteBullets();
	while (LPdx->retrunList() != NULL) LPdx->deleteBullets();
}


//restituisce il puntatore delle due liste di bullet del Bunker2
ptr_BulletsList Bunker2::returnLP(int n) {
	if (n == 1) return LPsx;
	else if (n == 2) return LPdx;
	else if (n == 3) return LPcentrale;
}