#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include "SolarSystem.h"
#include "Mapp.h"
#include "PlanetSurface.h"
#include "Spaceship.h"
#include "BulletsList.h"
using namespace std;

int main() {
	srand((unsigned)time(0));  
	Mapp mapp = Mapp();     //crea una mappa
	mapp.printMapp(1,1);    //stampa la mappa inziale
	char k = '2';
	while (k != VK_RETURN) k = _getch();  //finchè non si preme il tasto "invio" il gioco non va avanti

	etichetta:
	Spaceship nav_SS = Spaceship();     //crea la navicella
	SolarSystem x = SolarSystem(nav_SS);   //crea il sistema solare
	if (x.ifPianetiSovrapposti()) goto etichetta;  //controlla se la funzione random a creato piu pianeti con le stesse coordiante (sovrapposti), in tal caso riparte dall'etichetta quindi ricrea l'universo
	bool planetEnter = false;    //booleano che indica se si è entrati in un pianeta
	bool pianetaDistrutto = false;  //booleano che indica se si è distrutto un pianeta 
	int numeroSS = 1;         //numero del sistema solare
	int cicloSpari = 0;       //numero per dare un criterio agli spari dei bunker (viene incrementato fino a 12 poi resettato, quando assume determinati valori i bunker sparano)
	bool trashBullets = true;   //serve per decidere se cancellare o meno tutti i proiettili in gioco


	while (nav_SS.spaceshipIsAlive()) { //finche la navicella è in vita
		x.setMappUniverso(nav_SS);   //setta la mappa del sistema solare attuale
		x.printMapp();            //stampa la mappa del sistema solare attuale
		char n = x.interationSpaceship(nav_SS, planetEnter, numeroSS);   //si interagisce con la navicella (gli si da il comando da tastiera e viene svolto)
		while ((planetEnter) && (nav_SS.spaceshipIsAlive())) {   //se la navicella ha ancora vita e si è entrato in un pianeta (attivando quindi il booleano "planetEnter")
			x.pianetaCorrente(nav_SS, n)->azzerareListeBullets(nav_SS, trashBullets);   //se il booleano "trashBullets" è attivo, allora si eliminano tutti i proiettili presenti in gioco (e poi viene settato a false cosi da non ripetersi)
			x.pianetaCorrente(nav_SS, n)->printMapp();  //stampa la mappa del pianeta
			char m = x.pianetaCorrente(nav_SS, n)->interationSpaceshipPlanetSurface(nav_SS, pianetaDistrutto); //si interagisce con la navicella (gli si da il comando da tastiera e viene svolto)
			x.pianetaCorrente(nav_SS, n)->sparaBunker(nav_SS, cicloSpari);  //si aggiorna la lista dei proiettili dei bunker (consente di sparare ai bunker)
			x.aggiornamentoListaBunker(nav_SS, n, x.pianetaCorrente(nav_SS, n)->ritornoBunkerList1(), x.pianetaCorrente(nav_SS, n)->ritornoBunkerList2());  //aggiorna le liste di bunker del pianeta cosi da sapere se è stato distrutto completamente o meno 
			x.pianetaCorrente(nav_SS, n)->setMappPlanetSurface(nav_SS, m, planetEnter);  //setta la mappa del pianeta
			nav_SS.fuelMinus(); //aggiorna il carburante della navicella
		}
		trashBullets = true;   //imposta il booleano a true cosi che la porssima volta che si entra in un pianeta si cancellano tutti i proiettili
		x.solarSystemChange(numeroSS); //cambia il sistema solare se necessario
	}
	//stampa la mappa di quando hai finito la vita, chiedendoti cosa tu voglia fare
	//premendo "n" il gioco finisce, premendo "y" il programma torna all'etichetta ricomnciando da capo e quindi creare di nuovo il primo sistema solare
	//altri tasti non sono accetati 
	mapp.printMapp(2,1); 
	char h = '2';
	while (h != 'n') {
		if (h == 'y')	goto etichetta;
		else h = _getch();
	}
	mapp.printMapp(3, 1); //in caso venisse premuto "n", allora il gioco finisce totalmente e veiene stampata la schermata di "game over"
	return 0;
}