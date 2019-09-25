#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "SolarSystem.h"
using namespace std;


SolarSystem::SolarSystem(Spaceship p) {
	int numberPlanets = ((rand() % 3) + 4);  //genera un numero casuale di pianeti (da 4 a 6)
	ptr_SS tmp = new SS();                   //crea un nuovo sistema solare
	tmp->numberSolarSystem = 1;
	tmp->puntatore_planet = creaListaPianeti(p, tmp->puntatore_planet, numberPlanets);   //crea una lista di pianeti
	tmp->completed = false;     //il sistema solare attualemte non è distrutto
	tmp->next = NULL;           //sistema solare successivo
	tmp->prev = NULL;           //sistema solare precedente 
	SSystem = tmp;
	tmp = NULL;
	delete tmp;
}


//metodo per aggiungere un sistema solare in coda
void SolarSystem::addSolarSystem(Spaceship p) {
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


//metodo per creare una lista di pianeti, aggiunge i pianeti in coda
//gli assegna le coordinate "x" e "y"
ptr_Planet SolarSystem::creaListaPianeti(Spaceship p, ptr_Planet head, int numberPlanets) {
	for (int i = 1; i <= numberPlanets; i++) {
		int xPlanet = ((rand() % 75) + 2);
		int yPlanet = ((rand() % 16) + 2);
		if ((xPlanet == 3) && (yPlanet == 3)) {  // fa un controllo per non piazzare un pianeta in matrice[3][3] in quanto 
			xPlanet++;                            // è la posizone inziale della navicella e verrebero sovrapposte
			yPlanet++;
		}
		if (head == NULL) {
			ptr_Planet tmp;
			tmp = new Planet();
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


//metodo per controllare se sono state assegnate due posizioni uguali a due pianeti diversi
//fa il paragone tra tutti i pianeti presenti con due cicli while
bool SolarSystem::ifPianetiSovrapposti() {
	ptr_Planet tmp1 = SSystem->puntatore_planet;
	ptr_Planet tmp2 = SSystem->puntatore_planet->next;
	while (tmp1 != NULL) {
		while (tmp2 != NULL) {
			if ((tmp1->xPlanet == tmp2->xPlanet) && (tmp1->yPlanet == tmp2->yPlanet)) return true;
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
		if (tmp1 != NULL) tmp2 = tmp1->next;
	}
	return false;
}



void SolarSystem::setMappUniverso(Spaceship p) {
	if (returnIfDestroyed()) addSolarSystem(p);  //se il sistema solare corrente è completato, allora ne viene aggiunto uno in coda
	Mapp::setMapp();    //setta la cornice
	setSolarSystemParameters(p.returnParameter(100), p.returnParameter(10), p.returnParameter(200), SSystem->numberSolarSystem);
	matrice[p.returnParameter(1)][p.returnParameter(2)] = 'Y';  //setta la posizione della navicella (ricorda la posizione in caso si entri in un pianeta)

	//se tutti i pianeti sono stati distrutti, viene aggiunto l'informazione nella mappa che il sistema solare è completato
	if (SSystem->completed) {
		matrice[85][6] = 'C';
		matrice[86][6] = 'O';
		matrice[87][6] = 'M';
		matrice[88][6] = 'P';
		matrice[89][6] = 'L';
		matrice[90][6] = 'E';
		matrice[91][6] = 'T';
		matrice[92][6] = 'A';
		matrice[93][6] = 'T';
		matrice[94][6] = 'O';
	}

	//setta 'O' per rappresentare i Pianeti in base alle loro coordinate se non ancora distrutti
	//setta 'X' per rappresentare i Pianeti in base alle loro coordinate se sono state distrutte
	ptr_Planet tmp = SSystem->puntatore_planet;
	while (tmp != NULL) {
		if ((tmp->listBunker1 == NULL) && (tmp->listBunker2 == NULL)) matrice[tmp->xPlanet][tmp->yPlanet] = 'X';
		else  matrice[tmp->xPlanet][tmp->yPlanet] = 'O';
		tmp = tmp->next;
	}
}


//assegna un valore ad un carattere, con il quale poi si indica alla navicella cosa deve fare
void SolarSystem::spostamentoUniverso(char& moveSpaceshipUniverso) {
	if (GetAsyncKeyState(VK_UP)) moveSpaceshipUniverso = 72;
	else if (GetAsyncKeyState(VK_LEFT)) moveSpaceshipUniverso = 75;
	else if (GetAsyncKeyState(VK_RIGHT)) moveSpaceshipUniverso = 77;
	else if (GetAsyncKeyState(VK_DOWN)) moveSpaceshipUniverso = 80;
	else if (GetAsyncKeyState(0x51)) moveSpaceshipUniverso = '2';
	else if (GetAsyncKeyState(' ')) moveSpaceshipUniverso = '2';
}


//metodo per fare interagire la navicella con il gioco all'interno dello scenario "sistema solare"
//commentato solo per il comando per andare a sinstra, i restati sono uguali o simili (non possono cambiare sistema solare)
char SolarSystem::interationSpaceship(Spaceship & p, bool& b, int& numeroSS) {
	char n;
	spostamentoUniverso(n);    
	if (n == 75) { //left
		if (!b) {
			//se il carattere a sinstra è vuoto allora si puo usare il metodo con cui si aggiornano i campi della navicella
			if (matrice[p.returnParameter(1) - 1][p.returnParameter(2)] == ' ') p.moveSpaceshipSolarSystem(n); 
			
			//se il carattere a sinistra non è vuoto e non corripsonde alla cornice, allora il booleano b diventa true
			//questo indica che ha incontrato un pianeta, e il booleano diventando true accosente ad entrare al pianeta 
			else if (p.returnParameter(1) > 1) b = true;
			
			//se il carattere a sinistra non è vuoto e corrisponde alla cornice, fa un controllo per vedere se esiste un sistema solare precedente
			//se esiste, allora vine decrementato il numero del sistema solare e al prossimo ciclo viene stampato il sistema solare precedente
			else if ((SSystem->prev != NULL) && (SSystem->prev->completed)) {
				numeroSS--;   //decremente il numero del sistema solare
				p.modificaCoordinateInCasoDiNuovoSistemaSolare(1);  //modifica le coordinate della navicella cosi da averla nella posizione corrispondente alla stessa riga
			}
		}
	}
	else if (n == 77) {
		if (!b) { //right
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
	return n;  //ritorna il valore del comando inserito, ovvero in quale direzione si deve muovere
}


//metodo che restituisce il pianeta in cui si è cercato di entrare 
//in base al movimento che avrebbe dovuto fare la navicella viene incrementato o decrementato di un'unità la coordinata "x" o "y"
//viene poi fatto il confronto fino a trovare all'intenro della lista di pianeti quello che corrisponde a quelle coordinate
//viene poi restituito il puntatore all'oggetto PlanetSurface relativo
ptr_PlanetSurface SolarSystem::pianetaCorrente(Spaceship p, char n) {
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


//fa un controllo su tutti i pianeti presenti nella lista di pianeti
//controlla ciascun pianeta ha entrambe le liste di bunker che puntano a NULLù
//se questo è verificato, allora viene impostato il campo "completed" a true ed indica che il sistema solare è stato completato
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


//metodo per spostare il puntatore al sistema solare corrente in avanti o indietro in base al numero in input
//scorre la lista finchè il numero in input non combacia con il numero del sistema solare
//per sapere da che parte deve scorrere la lista esegue dei confronti 
void SolarSystem::solarSystemChange(int i) {
	while (SSystem->numberSolarSystem != i) {
		if (i < SSystem->numberSolarSystem)        SSystem = SSystem->prev;
		else if (i > SSystem->numberSolarSystem)   SSystem = SSystem->next;
	}
	solarSystemDestroyed();
	SSystem->completed = returnIfDestroyed();
}


//restituisce se il sistema solare è stato distrutto
bool SolarSystem::returnIfDestroyed() {
	return SSystem->completed;
}

//metodo che aggiorna la lista dei bunker (se sono vuote oppure se sono ancora presenti dei bunker)
//questo perche le liste di bunker vengono modificate all'interno del'oggetto PlanetSurface, servono pero anche all'interno del SolarSysem
//in base al movimento che avrebbe dovuto fare la navicella viene incrementato o decrementato di un'unità la coordinata "x" o "y"
//viene poi fatto il confronto fino a trovare all'intenro della lista di pianeti quello che corrisponde a quelle coordinate
//viene poi passato il punatatore delle liste passate in input alle liste di bunker della struttra Planet
//servirà poi per sapere se il pianeta è stato distrutto o meno
void SolarSystem::aggiornamentoListaBunker(Spaceship p, char n, ptr_listaBunker1 head1, ptr_listaBunker2 head2) {
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
