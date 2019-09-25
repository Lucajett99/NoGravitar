#include <iostream>
#include "Bunker1.h"
using namespace std;



//assegna i valori all'oggetto Bunker1
//crea un’oggetto di tipo BulletsList da cui poi si potranno aggiunger i Bullet e permettere al bunker di sparare (sia sx che dx)
Bunker1::Bunker1(int x, int y, int life) {
	xBunker1 = x;
	yBunker1 = y;
	lifeBunker1 = life;
	LPsx = new BulletsList();
	LPdx = new BulletsList();
}


//restituisce la posizione del Bunker1
int Bunker1::coordinateBunker1(bool b) {
	if (b) return xBunker1;
	else return yBunker1;
}


//toglie una vita al Bunker1 (nel caso venga colpito dal un "Bullet" della spaceship)
void Bunker1::minusLife() {
	lifeBunker1--;
}


//ritorna la vita del Bunker1
int Bunker1::returnLife() {
	return lifeBunker1;
}


//metodo per aggiungere dei "Bullet" a ciascuna delle due liste di bullet che fanno parte del Bunker1
void Bunker1::addBulletSBunker1() {
	LPsx->addBullets(xBunker1, yBunker1, false);
	LPdx->addBullets(xBunker1, yBunker1, false);
}


//metodo per elminare i "Bullet" su ciascuna delle due liste di bullet che fanno parte del Bunker1
void Bunker1::deleteBulletSBunker1() {
	LPsx->deleteBullets();
	LPdx->deleteBullets();
}


//metodo utilizzato per eliminare tutti i "Bullet" presenti nelle due liste (viene usato quando si esce dal pianeta)
//siccome il metodo deleteBullets() elimina solo i bullet in testa alla lista, viene ripetuto in un ciclo while finche la lista non si svuota
//viene eseguito il ciclo per ciascuna delle tre liste bullet del Bunker1
//prima un ciclo per assegnare a tutti i Bunker1 il valore true al campo "eliminato", e uno successivo per eliminarli dalla lista
void Bunker1::deleteAllBulletsBunker1() {
	ptr_Bullet tmpSx = LPsx->retrunList();
	while (tmpSx != NULL) {
		tmpSx->eliminato = true;
		tmpSx = tmpSx->next;
	}
	ptr_Bullet tmpDx = LPdx->retrunList();
	while (tmpDx != NULL) {
		tmpDx->eliminato = true;
		tmpDx = tmpDx->next;
	}
	while (LPsx->retrunList() != NULL) LPsx->deleteBullets();
	while (LPdx->retrunList() != NULL) LPdx->deleteBullets();
}


//restituisce il puntatore delle due liste di bullet del Bunker1
ptr_BulletsList Bunker1::returnLP(int n) {
	if (n == 1) return LPsx;
	else if (n == 2) return LPdx;
}
