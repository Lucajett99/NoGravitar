#include <conio.h>
#include <iostream>
#include "Spaceship.h"
#include "BulletsList.h"

using namespace std;

//crea la navicella e setta la sua posizione iniziale 
Spaceship::Spaceship() {
	setMapp();
	p1 = 3;
	p2 = 3;
	p3 = 3;
	p4 = 3;
	life = 10;
	fuel = 1500;
	score = 0;
	LP = new BulletsList();
}


//modifica la nuova posizione della navicella del sistema solare
//prima di modificare le coordinate della navicella, fa un controllo per evitare che esca dalla mappa/cornice di gioco
void Spaceship::moveSpaceshipSolarSystem(char n) {
	if ((matrice[p1 - 1][p2] == ' ') && n == 75)           p1 = p1 - 1;			//SINISTRA---controllo margine
	else if ((matrice[p1 + 1][p2] == ' ') && n == 77)      p1 = p1 + 1;        	//DESTRA---controllo margine
	else if ((matrice[p1][p2 - 1] == ' ') && n == 72)	   p2 = p2 - 1;	        //SU---controllo marigine
	else if ((matrice[p1][p2 + 1] == ' ') && n == 80)	   p2 = p2 + 1;         //GIU---controllo margine
}


//modifica la nuova posizione della navicella del sistema solare
//prima di modificare le coordinate della navicella, fa un controllo per evitare che esca dalla mappa
//eccetto per il bordo superiore, che consente di uscire dal pianeta
void Spaceship::moveSpaceshipPlanet(char n) {
	if ((matrice[p3 - 1][p4] == ' ') && n == 75)           p3 = p3 - 1;			//SINISTRA---controllo margine
	else if ((matrice[p3 + 1][p4] == ' ') && n == 77)      p3 = p3 + 1;        	//DESTRA---controllo margine
	else if (n == 72)	                                   p4 = p4 - 1;	         //SU---controllo marigine
	else if ((matrice[p3][p4] == ' ') && n == 80)	       p4 = p4 + 1;         //GIU---controllo margine
}


//ritorna i campi della navicella in base al numero in input 
int Spaceship::returnParameter(int i) {
	if (i == 1) return p1;
	else if (i == 2) return p2;
	else if (i == 3) return p3;
	else if (i == 4) return p4;
	else if (i == 10) return life;
	else if (i == 100) return fuel;
	else if (i == 200) return score;
}


//diminuisce di un'unità il carburante
void Spaceship::fuelMinus() {
	fuel--;
}


//diminuisce di un'unità la vita
void Spaceship::lifeMinus() {
	life--;
}


//aumenta il punteggio in base al numero in input (in base a quale Bunker viene distrutto)
void Spaceship::setScore(int i) {
	if (i == 1) score += 3;
	else if (i == 2) score += 5;
}


//metodo che imposta sempre la stessa posizione iniziale della navicella all'interno di un pianeta 
void Spaceship::setInitialPosition() {
	p3 = 3;
	p4 = 3;
}


//aumenta il carburante in base al numero in input (in base a quale tipo di carburante viene prelevato)
void Spaceship::fuelPlus(int i) {
	if (i == 0) fuel = fuel + 500;
	else if (i == 1) fuel = fuel + 100;
}


//ritorna se la navicella è ancora in vita e quindi se continuare o meno il gioco
bool Spaceship::spaceshipIsAlive() {
	if ((fuel >= 1) && (life >= 1)) return true;
	else return false;
}


//metodo per modificare le coordinate del sistema solare P1 e P2 
//in modo tale da avere la navicella nella stessa riga e nella posizione corretta una volta che si cambia sistema solare
void Spaceship::modificaCoordinateInCasoDiNuovoSistemaSolare(int i) {
	if (i == 0) p1 = 1;
	else if (i == 1) p1 = 77;
}


//aggiunge un Bullet alla liste di bullet (permette alla navicella di sparare)
void Spaceship::addBulletSPaceship() {
	LP->addBullets(p3, p4, false);
}


//elimina un Bullet dalla lista di buller (quando raggiunge un elemento della superfice)
void Spaceship::deleteBulletSPaceship() {
	LP->deleteBullets();
}


//elimina tutti i Bullet presenti nella lista di bullet 
//usato per pulire la lista nel caso in cui si abbandoni il pianeta 
//prima un ciclo per assegnare a tutti i bullet il valore ture al campo "eliminato" 
//poi un secondo ciclo che elimmina tutti i bullet in testa alla lista finche la lista non è vuota
void Spaceship::deleteAllBulletsSpaceship() {
	ptr_Bullet tmp = LP->retrunList();
	while (tmp != NULL) {
		tmp->eliminato = true;
		tmp = tmp->next;
	}
	while (LP->retrunList() != NULL) LP->deleteBullets();
}


//ritorna la lista di Bullet
ptr_BulletsList Spaceship::returnLP() {
	return LP;
}
