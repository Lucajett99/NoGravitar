#include <iostream>
#include "BulletsList.h"
#include "Spaceship.h"

using namespace std;


//setta il puntatore alla struttura "Bullet" a NULL
BulletsList::BulletsList() {
	listaProiettili = NULL;
}


//metodo per aggiunere un "Bullet" alla lista di bullet
//aggiunge in coda
//gli passa le coordinate e il valore falso al campo "eliminato" in quanto al momento non sono da eliminare
void BulletsList::addBullets(int x, int y, bool b) {
	if (listaProiettili == NULL) {
		listaProiettili = new Bullet();
		listaProiettili->xBullet = x;
		listaProiettili->yBullet = y;
		listaProiettili->eliminato = b;
		listaProiettili->next = NULL;
	}
	else if (listaProiettili->next == NULL) {
		listaProiettili->next = new Bullet();
		listaProiettili->next->xBullet = x;
		listaProiettili->next->yBullet = y;
		listaProiettili->next->eliminato = b;
		listaProiettili->next->next = NULL;
	}
	else {
		ptr_Bullet tmp, tmpOld;
		tmpOld = listaProiettili;
		tmp = listaProiettili->next;
		while (tmpOld->next->next != NULL) {
			tmp = tmp->next;
			tmpOld = tmpOld->next;
		}
		tmp->next = new Bullet();
		tmp->next->xBullet = x;
		tmp->next->yBullet = y;
		tmp->next->eliminato = b;
		tmp->next->next = NULL;
		tmp = NULL;
		tmpOld = NULL;
		delete tmp;
		delete tmpOld;
	}
}


//metodo per eliminare un "Bullet" alla lista di bullet
//metodo scritto in questo modo siccome l'unico "Bullet" che puo essere eliminto è quello in testa alla lista
void BulletsList::deleteBullets() {
	if (listaProiettili != NULL) {
		if (listaProiettili->eliminato == true) {
			if (listaProiettili->next != NULL) {
				ptr_Bullet tmp = listaProiettili;
				listaProiettili = listaProiettili->next;
				delete tmp;
			}
			else {
				ptr_Bullet tmp = listaProiettili;
				listaProiettili = NULL;
				delete tmp;
			}
		}
	}
}


//ritorna il puntatore alla lista di proiettili 
ptr_Bullet BulletsList::retrunList() {
	return listaProiettili;
}


