#include <iostream>
#include <Windows.h>
#include "PlanetSurface.h"
using namespace std;


//metodo che costruisce l'oggetto "PlanetSurface"
//vengono passati come parametri la "Spaceship" e i puntatori delle due liste di Bunker presenti nella struttura "Planet"
//nei caratteri della superfice che "salgono" o "scendono" possono venire piazzati dei bunker
//nei caratteri della superfice che rimangono sullo stesso livello possono venire piazzati del carburante
PlanetSurface::PlanetSurface(Spaceship spaceship, ptr_listaBunker1& head1, ptr_listaBunker2& head2) {
	//setta la schermata inziale 
	setMapp();
	setPlanetSurfaceParameters(spaceship.returnParameter(100), spaceship.returnParameter(10), spaceship.returnParameter(200));
	matrice[spaceship.returnParameter(3)][spaceship.returnParameter(4)] = 'Y';

	//setta la posizione del primo carattere che va a formare la superficie del pianeta (da 10 a 16)
	int valorePrecedente = ((rand() % 7) + 10);

	//valore successivo, serivirà poi per fare il confronto con valorePrcedente per formare una superficie 
	//dove lo scostamento tra un carattere e l'altro è solo di 1
	int valoreSuccessivo = 0;

	//setta il resto della superficie facendo dei confronti per avere uno scostamento (negativo o positivo) al massimo di 1
	int lunghezzaSuperficie = 1;   //serve per impostare la lunghezza della superficie del pianeta
	int numeroBunker1 = 0;         //serve per avere un limite di Buneker1 nel pianeta
	int numeroBunker2 = 0;         //serve per avere un limite di Buneker2 nel pianeta
	int tmp = 0;                   //serve per non piazzare due bunker troppo vicini 

	while (lunghezzaSuperficie <= 77) { //per tutta la lunghezza della zona adibita alla superfice
		valoreSuccessivo = (rand() % 16) + 1; //genera un numero che non scende mai sotto il 16 (limite massio inferiore della superfice)
		int riempimento = 0;    //variabile per rimepire e colorare la parte inferiore della superfice 

		//se il valore di "valoreSuccessivo" è maggiore di 1 rispetto a "valorePrecedente", allora la superficie salirà di carattere
		if ((valoreSuccessivo == valorePrecedente - 1) && (valoreSuccessivo >= 10)) {
			matrice[lunghezzaSuperficie][valoreSuccessivo] = '/';
			riempimento = valoreSuccessivo + 1;

			while (riempimento < 20) {    //serve per inserire i puntini al di sotto della superficie (per poi colorarla)
				matrice[lunghezzaSuperficie][riempimento] = 34;
				riempimento++;
			}

			valorePrecedente = valoreSuccessivo; //si fa il passaggio del valore per il prossimo confronto 

			//qui si modifica (o non modifca) la lista di Bunker1
			//ci sono dei parametri per non mettere due bunker troppo vicini, non metterne troppi e per rendere le varie posizioni piu casuali possibili
			//se vengono verificati i vari parametri allora viene aggiunto un bunker alla lista
			if ((lunghezzaSuperficie >= tmp + 10) && (numeroBunker1 <= 1) && (lunghezzaSuperficie % ((rand() % 15) + 1) == 0)) {
				head1 = creaBunkerList1(head1, lunghezzaSuperficie, valoreSuccessivo - 1);
				tmp = lunghezzaSuperficie;   	//si aggiorna la posizione in "x" dell'ultimo buker (per non farlo troppo vicino con il prossimo bunker)
				numeroBunker1++;   //si incrementa il numero di bunker1 di 1 per non mettere troppi bunker
			}
			if ((lunghezzaSuperficie >= tmp + 10) && (numeroBunker2 < 1) && (lunghezzaSuperficie % 5 == 0) && (matrice[lunghezzaSuperficie][valoreSuccessivo - 1] == ' ')) {
				head2 = creaBunkerList2(head2, lunghezzaSuperficie, valoreSuccessivo - 1);
				tmp = lunghezzaSuperficie;
				numeroBunker2++;
			}
			lunghezzaSuperficie++;
		}

		//ragionamento uguale al precdente però scendendo di un carattere
		else if ((valoreSuccessivo == valorePrecedente + 1) && (valoreSuccessivo >= 10)) {
			matrice[lunghezzaSuperficie][valoreSuccessivo - 1] = 92;
			riempimento = valoreSuccessivo;
			while (riempimento < 20) {
				matrice[lunghezzaSuperficie][riempimento] = 34;
				riempimento++;
			}
			valorePrecedente = valoreSuccessivo;
			if ((lunghezzaSuperficie >= tmp + 10) && (numeroBunker1 <= 2) && (lunghezzaSuperficie % ((rand() % 3) + 4) == 0)) {
				head1 = creaBunkerList1(head1, lunghezzaSuperficie, valoreSuccessivo - 2);
				tmp = lunghezzaSuperficie;
				numeroBunker1++;
			}
			if ((lunghezzaSuperficie >= tmp + 10) && (numeroBunker2 < 1) && (lunghezzaSuperficie % 5 == 0) && (matrice[lunghezzaSuperficie][valoreSuccessivo - 1] == ' ')) {
				head2 = creaBunkerList2(head2, lunghezzaSuperficie, valoreSuccessivo - 2);
				tmp = lunghezzaSuperficie;
				numeroBunker2++;
			}
			lunghezzaSuperficie++;
		}

		//qui invece vengono sistemati sopra la superfice i due tipi di carburante sempre in modo casuale
		//il procedimento è simile a quello precdente però non ci sono limiti di unità e limiti sulla distanza 
		else if ((valoreSuccessivo == valorePrecedente) && (valoreSuccessivo >= 10)) {
			matrice[lunghezzaSuperficie][valoreSuccessivo] = 34;
			riempimento = valoreSuccessivo + 1;
			while (riempimento < 20) {
				matrice[lunghezzaSuperficie][riempimento] = 34;
				riempimento++;
			}
			if ((lunghezzaSuperficie % 25) == 0) matrice[lunghezzaSuperficie][valoreSuccessivo - 1] = 'C';
			if ((lunghezzaSuperficie % 10) == 0) matrice[lunghezzaSuperficie][valoreSuccessivo - 1] = 'c';
			lunghezzaSuperficie++;
		}
	}

	//vengono poi assegnati i valori delle due liste ai campi dell'oggetto in questione
	LBunker1 = head1;
	LBunker2 = head2;

	//qui si scorre tutta la lista di bunker e vengono settate sulla matrice i caratteri dei vari bunker in base alle loro posizioni 
	ptr_listaBunker1 tmp1 = head1;
	while (tmp1 != NULL) {
		matrice[tmp1->b1->coordinateBunker1(true)][tmp1->b1->coordinateBunker1(false)] = 'b';
		tmp1 = tmp1->next;
	}

	ptr_listaBunker2 tmp2 = head2;
	while (tmp2 != NULL) {
		matrice[tmp2->b2->coordinateBunker2(true)][tmp2->b2->coordinateBunker2(false)] = 'B';
		tmp2 = tmp2->next;
	}

}

//metodo per creare la lista di tipo Bunker1, inserimento in coda
//gli viene passato in input la testa della lista e le coordinate prese dalla superfice (un carattere sopra)
ptr_listaBunker1 PlanetSurface::creaBunkerList1(ptr_listaBunker1 head, int xB, int yB) {
	if (head == NULL) {
		head = new listaBunker1();
		head->b1 = new Bunker1(xB, yB, 3);
		head->next = NULL;
	}
	else if (head->next == NULL) {
		head->next = new listaBunker1();
		head->next->b1 = new Bunker1(xB, yB, 3);
		head->next->next = NULL;
	}
	else {
		ptr_listaBunker1 tmpOld, tmpNew;
		tmpOld = head;
		tmpNew = head->next;
		while (tmpOld->next->next != NULL) {
			tmpOld = tmpNew;
			tmpNew = tmpNew->next;
		}
		ptr_listaBunker1 tmp;
		tmp = new listaBunker1();
		tmp->b1 = new Bunker1(xB, yB, 3);
		tmp->next = NULL;
		tmpNew->next = tmp;
		tmp = NULL;
		tmpOld = NULL;
		tmpNew = NULL;
		delete tmp;
		delete tmpOld;
		delete tmpNew;
	}
	return head;
}


//metodo per creare la lista di tipo Bunker2, inserimento in coda
//gli viene passato in input la testa della lista e le coordinate prese dalla superfice (un carattere sopra)
ptr_listaBunker2 PlanetSurface::creaBunkerList2(ptr_listaBunker2 head, int xB, int yB) {
	if (head == NULL) {
		head = new listaBunker2();
		head->b2 = new Bunker2(xB, yB, 3);
		head->next = NULL;
	}
	else if (head->next == NULL) {
		head->next = new listaBunker2();
		head->next->b2 = new Bunker2(xB, yB, 3);
		head->next->next = NULL;
	}
	else {
		ptr_listaBunker2 tmpOld, tmpNew;
		tmpOld = head;
		tmpNew = head->next;
		while (tmpOld->next->next != NULL) {
			tmpOld = tmpNew;
			tmpNew = tmpNew->next;
		}
		ptr_listaBunker2 tmp;
		tmp = new listaBunker2();
		tmp->b2 = new Bunker2(xB, yB, 3);
		tmp->next = NULL;
		tmpNew->next = tmp;
		tmp = NULL;
		tmpOld = NULL;
		tmpNew = NULL;
		delete tmp;
		delete tmpOld;
		delete tmpNew;
	}
	return head;
}

//assegna un valore ad un carattere, con il quale poi si indica alla navicella cosa deve fare
void PlanetSurface::spostamentoPlaetSurface(char& moveSpaceshipUniverso) {
	if (GetAsyncKeyState(VK_UP)) moveSpaceshipUniverso = 72;
	else if (GetAsyncKeyState(VK_LEFT)) moveSpaceshipUniverso = 75;
	else if (GetAsyncKeyState(VK_RIGHT)) moveSpaceshipUniverso = 77;
	else if (GetAsyncKeyState(VK_DOWN)) moveSpaceshipUniverso = 80;
	else if (GetAsyncKeyState(0x51)) moveSpaceshipUniverso = 'q';
	else if (GetAsyncKeyState(' ')) moveSpaceshipUniverso = 'z';
	else moveSpaceshipUniverso = 'w';
}


//metodo per fare interagire la navicella con il gioco all'interno dello scenario "pianeta"
//in tutti le direzioni di spostamento, fa prima un controllo se il raggio traente non è attivato, in caso contrario non ci si puo muovere
char PlanetSurface::interationSpaceshipPlanetSurface(Spaceship & p, bool& pianetaDistrutto) {
	char n;
	spostamentoPlaetSurface(n);

	//left
	if ((n == 75) && (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] != '|')) {   //controllo raggio traente attivo
		//se il carattere a sinstra è vuoto allora si puo usare il metodo con cui si aggiornano i campi della navicella
		if (matrice[p.returnParameter(3) - 1][p.returnParameter(4)] == ' ') p.moveSpaceshipPlanet(n);
		else {
			//se il carattere a sinistra non è vuoto allora viene tolta una vita alla navicella (eccetto che non si tratti di del bordo)
			if (p.returnParameter(3) > 1) p.lifeMinus();
		}
	}

	//right, stesso ragionamento per left
	else if ((n == 77) && (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] != '|')) {
		if (matrice[p.returnParameter(3) + 1][p.returnParameter(4)] == ' ') p.moveSpaceshipPlanet(n);
		else {
			if (p.returnParameter(3) < 77) p.lifeMinus();
		}
	}

	//up, qui non ci sono controlli in quanto il vordo superiore serve per uscire dal pianeta
	else if ((n == 72) && (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] != '|')) {
		p.moveSpaceshipPlanet(n);
	}

	//down, qui non c'è il controllo della coordinata "y" in quanto non si arriverà mai al bordo inferiore perche presente la superfice
	else if ((n == 80) && (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] != '|')) {
		if (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] == ' ')p.moveSpaceshipPlanet(n);
		else  p.lifeMinus();
	}

	else if (n == 'q') raggioTraenteUscente(p);  //se il valore è uguale al carattere 'q' allora viene attivato il raggio traente
	else if (n == 'w') raggioTraenteEntrante(p); //se il valore è uguale al carattere 'w' allora viene fatto rientrare il raggio traente
	else if (n == 'z') {          //se il valore è uguale al carattere 'z' allora viene aggiunto un Bullet alla lista di bullet della navicella
		p.addBulletSPaceship();
	}
	refreshSpaceship(p, LBunker1, LBunker2); //metodo per aggiornare i proiettili della navicella e per modificare le liste dei bunekr
	return n;
}


//setta i vari caratteri della matrice del pianeta
void PlanetSurface::setMappPlanetSurface(Spaceship & p, char n, bool& uscitaPianeta) {
	setPlanetSurfaceParameters(p.returnParameter(100), p.returnParameter(10), p.returnParameter(200)); //informazioni generali

	//setta la posizione della navicella 
	matrice[p.returnParameter(3)][p.returnParameter(4)] = 'Y';

	//cancellano la posizione vecchia della navicella
	if (matrice[p.returnParameter(3) + 1][p.returnParameter(4)] == 'Y') matrice[p.returnParameter(3) + 1][p.returnParameter(4)] = ' ';
	if (matrice[p.returnParameter(3) - 1][p.returnParameter(4)] == 'Y') matrice[p.returnParameter(3) - 1][p.returnParameter(4)] = ' ';
	if (matrice[p.returnParameter(3)][p.returnParameter(4) - 1] == 'Y') matrice[p.returnParameter(3)][p.returnParameter(4) - 1] = ' ';
	//se il comando è quello di spostarsi verso l'alto
	//se non si cerca di superare il bordo superiore allora semplicemente cancella la posizione vecchia
	if (n == 72) {
		if (p.returnParameter(4) >= 1) {
			if (matrice[p.returnParameter(3)][p.returnParameter(4) + 1] == 'Y') matrice[p.returnParameter(3)][p.returnParameter(4) + 1] = ' ';
		}
		//se invece si cerca di superare il bordo superiore, allora vuol dire che si sta cercando di uscire dal pianeta
		else {
			uscitaPianeta = false;    //si disattiva il booleano che indica se si è dentro o meno ad un pianeta
			matrice[p.returnParameter(3)][p.returnParameter(4)] = 205;      //elimina il carattere della navicella
			matrice[p.returnParameter(3)][p.returnParameter(4) + 1] = ' ';  //elimina il carattere della navicella
			p.setInitialPosition();   //si setta la posizione inziale della navicella nelle coordinate P3 e P4 (quelle all'interno del pianeta)
			matrice[p.returnParameter(3)][p.returnParameter(4)] = 'Y';      //imposta il carattere della navicella appena si entra nel pianeta
		}
	}
}

//setta graficamente la matrice nel caso si voglia interagire con il raggio traente
//ATTENZIONE: si puo attivare solo se non ci sono degli spari della navicella in giro, quindi la sua lista di proiettili è vuota
//crea il a partire dal carattere sotto la navicella fino ad un carattere diverso dallo spazio vuoto o dagli spari dei bunker
//se incontra un carattere della superfice si bolcca
//se incontra un carburante, lo elimina dalla grafica e aggiorna il parametro carburante della navicella 
void PlanetSurface::raggioTraenteUscente(Spaceship & p) {
	int x = p.returnParameter(3);
	int y = p.returnParameter(4);
	if (p.returnLP()->retrunList() == NULL) {
		while ((matrice[x][y + 1] == ' ') || (matrice[x][y + 1] == 'c') || (matrice[x][y + 1] == 'C') || (matrice[x][y + 1] == '.')) {
			if (matrice[x][y + 1] == 'C') {
				matrice[x][y + 1] = ' ';
				p.fuelPlus(0);
			}
			else if (matrice[x][y + 1] == 'c') {
				matrice[x][y + 1] = ' ';
				p.fuelPlus(1);
			}
			else {
				matrice[x][y + 1] = '|';
				if (matrice[x - 1][y + 1] == '.') matrice[x - 1][y + 1] = ' ';
				if (matrice[x + 1][y + 1] == '.') matrice[x + 1][y + 1] = ' ';
			}
			y++;
		}
	}
}


//setta graficamente la matrice nel caso si voglia interagire con il raggio traente
//modifca la matrice cancellando tutti il raggio
void PlanetSurface::raggioTraenteEntrante(Spaceship p) {
	int x = p.returnParameter(3);
	int y = p.returnParameter(4);
	while (matrice[x][y + 1] == '|') {
		matrice[x][y + 1] = ' ';
		y++;
	}
}


//metodo per aggiornare automaticamente la lista di proiettili dei due tipi di bunker
//viene gerato un ciclo di numeri che serve per dettare i tempi degli spari dei bunker (si resetta quando arriva a 12)
void PlanetSurface::sparaBunker(Spaceship & p, int& i) {
	refreshBunker1(p, LBunker1, i);
	refreshBunker2(p, LBunker2, i);
	i++;
	if (i == 12) i = 0;
}


//metodo per aggiungere ed eliminare i proittili alla lista di proiettili del Bunker1
//utilizzato anche per aggiornare ad ogni ciclo la posizione di ciascun poriettile e di settarne correttamente la posizione sulla schermata
void PlanetSurface::refreshBunker1(Spaceship & p, ptr_listaBunker1 & head1, int i) {
	ptr_listaBunker1 tmp1 = head1;
	//vengono aggiunti i proittili alla lista
	if ((i == 0) || (i == 5)) {  //serve per creare un criterio per aggiungere i proiettili
		while (tmp1 != NULL) {
			if (matrice[tmp1->b1->coordinateBunker1(true)][tmp1->b1->coordinateBunker1(false)] == 'b') tmp1->b1->addBulletSBunker1();
			tmp1 = tmp1->next;
		}
	}
	tmp1 = head1;

	//serve per aggiornare la posizione dei proettili sia come coordinate sia graficamente nella schermata
	while (tmp1 != NULL) {
		ptr_Bullet tmpSx = tmp1->b1->returnLP(1)->retrunList();
		while (tmpSx != NULL) {
			tmpSx->xBullet--;   //direzione della lista sinistra di proiettili 
			tmpSx->yBullet--;   //direzione della lista sinistra di proiettili
			//setta graficamente la posizione del nuovo proiettile e cancella quella vecchia
			//gli spari sono secondari graficamente al raggio traente e alla navicella
			if ((matrice[tmpSx->xBullet][tmpSx->yBullet] == ' ') || (matrice[tmpSx->xBullet][tmpSx->yBullet] == '.')) {
				if (matrice[tmpSx->xBullet - 1][tmpSx->yBullet - 1] != '|') matrice[tmpSx->xBullet][tmpSx->yBullet] = '.';
				if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != '|') {
					if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != 'b') matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				}
			}
			//se la coordinata y del proiettile raggiunge il bordo superiore, allora gli viene assegnato il valore true (cosi poi da cancellarlo)
			if (tmpSx->yBullet <= 0) {
				matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				tmpSx->eliminato = true;
			}
			//se la coordinata x del proiettile raggiunge il bordo sinistro, allora gli viene assegnato il valore true (cosi poi da cancellarlo)
			if (tmpSx->xBullet <= 0) {
				matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				tmpSx->eliminato = true;
			}
			//se la posizione del proiettile corrisponde alla posizione della naviella, viene tolta una vita alla navicella
			if (matrice[tmpSx->xBullet][tmpSx->yBullet] == 'Y') {
				p.lifeMinus();
				if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != 'b') matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
			}
			//se la posizione del proiettile corrisponde aall'angolo alto/dx, gli viene assegnato il valore true (cosi poi da cancellarlo)
			//e viene ripristinato graficamente 
			if ((tmpSx->xBullet == 0) && (tmpSx->yBullet == 0)) {
				tmpSx->eliminato = true;
				matrice[0][0] = 201;
			}
			tmpSx = tmpSx->next;
		}

		//stesso procedimento visto per la parte sinistra, pero spostato nella parte destra
		ptr_Bullet tmpDx = tmp1->b1->returnLP(2)->retrunList();
		while (tmpDx != NULL) {
			tmpDx->xBullet++;
			tmpDx->yBullet--;
			if ((matrice[tmpDx->xBullet][tmpDx->yBullet] == ' ') || (matrice[tmpDx->xBullet][tmpDx->yBullet] == '.')) {
				if (matrice[tmpDx->xBullet + 1][tmpDx->yBullet - 1] != '|') matrice[tmpDx->xBullet][tmpDx->yBullet] = '.';
				if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != '|') {
					if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != 'b') matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
				}
			}
			if (tmpDx->yBullet <= 0) {
				tmpDx->eliminato = true;
				matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
			}
			if (tmpDx->xBullet >= 78) {
				matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
				tmpDx->eliminato = true;
			}
			if (matrice[tmpDx->xBullet][tmpDx->yBullet] == 'Y') {
				p.lifeMinus();
				if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != 'b') matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
			}
			if ((tmpDx->xBullet == 78) && (tmpDx->yBullet == 0)) {
				tmpDx->eliminato = true;
				matrice[78][0] = 203;
			}
			tmpDx = tmpDx->next;
		}
		tmp1 = tmp1->next;
	}
	tmp1 = head1;

	//elimina i bullet che hanno toccato i vari bordi (quindi con il campo "eliminato" impostato in true)
	while (tmp1 != NULL) {
		tmp1->b1->deleteBulletSBunker1();
		tmp1 = tmp1->next;
	}
}


//metodo uguale a refreshBunker1, con l'aggiunta di una terza lista centrale dove pero il ragionamento è lo stesso di quella sx e dx
void PlanetSurface::refreshBunker2(Spaceship & p, ptr_listaBunker2 & head2, int i) {
	ptr_listaBunker2 tmp2 = head2;
	if (i == 7) {
		while (tmp2 != NULL) {
			if (matrice[tmp2->b2->coordinateBunker2(true)][tmp2->b2->coordinateBunker2(false)] == 'B')tmp2->b2->addBulletSBunker2();
			tmp2 = tmp2->next;
		}
	}
	tmp2 = head2;
	while (tmp2 != NULL) {
		ptr_Bullet tmpSx = tmp2->b2->returnLP(1)->retrunList();
		while (tmpSx != NULL) {
			tmpSx->xBullet--;
			tmpSx->yBullet--;
			if ((matrice[tmpSx->xBullet][tmpSx->yBullet] == ' ') || (matrice[tmpSx->xBullet][tmpSx->yBullet] == '.')) {
				if (matrice[tmpSx->xBullet - 1][tmpSx->yBullet - 1] != '|') matrice[tmpSx->xBullet][tmpSx->yBullet] = '.';
				if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != '|') {
					if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != 'B') matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				}
			}
			if (tmpSx->yBullet <= 0) {
				matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				tmpSx->eliminato = true;
			}
			if (tmpSx->xBullet <= 0) {
				matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
				tmpSx->eliminato = true;
			}
			if (matrice[tmpSx->xBullet][tmpSx->yBullet] == 'Y') {
				p.lifeMinus();
				if (matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] != 'B') matrice[tmpSx->xBullet + 1][tmpSx->yBullet + 1] = ' ';
			}
			if ((tmpSx->xBullet == 0) && (tmpSx->yBullet == 0)) {
				tmpSx->eliminato = true;
				matrice[0][0] = 201;
			}
			tmpSx = tmpSx->next;
		}
		ptr_Bullet tmpCentrale = tmp2->b2->returnLP(3)->retrunList();
		while (tmpCentrale != NULL) {
			tmpCentrale->yBullet--;
			if ((matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] == ' ') || (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] == '.')) {
				matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] = '.';
				if (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] != 'B') matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] = ' ';
			}
			if (tmpCentrale->yBullet <= 0) {
				tmpCentrale->eliminato = true;
				if (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] != 'B') matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] = ' ';
			}
			else if (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] == 'Y') {
				p.lifeMinus();
				if (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] == 'Y')
					if ((matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] != '|') && (matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] != 'B')) matrice[tmpCentrale->xBullet][tmpCentrale->yBullet + 1] = ' ';
			}
			tmpCentrale = tmpCentrale->next;
		}
		ptr_Bullet tmpDx = tmp2->b2->returnLP(2)->retrunList();
		while (tmpDx != NULL) {
			tmpDx->xBullet++;
			tmpDx->yBullet--;
			if ((matrice[tmpDx->xBullet][tmpDx->yBullet] == ' ') || (matrice[tmpDx->xBullet][tmpDx->yBullet] == '.')) {
				if (matrice[tmpDx->xBullet + 1][tmpDx->yBullet - 1] != '|') matrice[tmpDx->xBullet][tmpDx->yBullet] = '.';
				if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != '|') {
					if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != 'B') matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
				}
			}
			if (tmpDx->yBullet <= 0) {
				tmpDx->eliminato = true;
				matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
			}
			if (tmpDx->xBullet >= 78) {
				matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
				tmpDx->eliminato = true;
			}
			if (matrice[tmpDx->xBullet][tmpDx->yBullet] == 'Y') {
				p.lifeMinus();
				if (matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] != 'B') matrice[tmpDx->xBullet - 1][tmpDx->yBullet + 1] = ' ';
			}
			if ((tmpDx->xBullet == 78) && (tmpDx->yBullet == 0)) {
				tmpDx->eliminato = true;
				matrice[78][0] = 203;
			}
			tmpDx = tmpDx->next;
		}
		tmp2 = tmp2->next;
	}
	tmp2 = head2;
	while (tmp2 != NULL) {
		tmp2->b2->deleteBulletSBunker2();
		tmp2 = tmp2->next;
	}
}


//metodo per aggiungere ed eliminare i proittili alla lista di proiettili della navicella
//utilizzato anche per aggiornare ad ogni ciclo la posizione di ciascun poriettile e di settarne correttamente la posizione sulla schermata
void PlanetSurface::refreshSpaceship(Spaceship & p, ptr_listaBunker1 & head1, ptr_listaBunker2 & head2) {
	ptr_Bullet tmp = p.returnLP()->retrunList();
	int xx = 0;
	int yy = 0;

	//serve per aggiornare la posizione dei proettili sia come coordinate sia graficamente nella schermata
	while (tmp != NULL) {
		matrice[tmp->xBullet][tmp->yBullet] = ' '; //cancella la posizione vecchia
		tmp->yBullet++;             //modifica le coordinate

		//setta la nuova posizione nella schermata se incontra un carattere vuoto
		if ((matrice[tmp->xBullet][tmp->yBullet] == ' ') || (matrice[tmp->xBullet][tmp->yBullet] == '.')) {
			matrice[tmp->xBullet][tmp->yBullet] = ':';
		}

		//se incontra un carattere che rappresenta un Bunker1
		else if (matrice[tmp->xBullet][tmp->yBullet] == 'b') {
			ptr_listaBunker1 tmp1 = head1;
			//cerca all'interno della lista il bunker che corrisponde con le coordinate
			while ((tmp1->b1->coordinateBunker1(true) != tmp->xBullet) && (tmp1->b1->coordinateBunker1(false) != tmp->yBullet)) tmp1 = tmp1->next;
			tmp->eliminato = true;  //assegna il valore true al proiettile per poi essere eliminato
			tmp1->b1->minusLife();  //toglie una vita al bunker
			xx = tmp->xBullet;     //tiene in memoria la posizione del bunker (serve poi per vedere se ha finito le vite e quindi deve essere eliminato)
			yy = tmp->yBullet;     //tiene in memoria la posizione del bunker (serve poi per vedere se ha finito le vite e quindi deve essere eliminato)
		}

		//stesso ragionamento per Bunker2
		else if (matrice[tmp->xBullet][tmp->yBullet] == 'B') {
			ptr_listaBunker2 tmp2 = head2;
			while ((tmp2->b2->coordinateBunker2(true) != tmp->xBullet) && (tmp2->b2->coordinateBunker2(false) != tmp->yBullet)) tmp2 = tmp2->next;
			tmp->eliminato = true;
			tmp2->b2->minusLife();
			xx = tmp->xBullet;
			yy = tmp->yBullet;
		}

		//se incontra un carattere che rappresente la superfice o il carburante viene semplicemente impostato "eliminato" a true
		else tmp->eliminato = true;

		tmp = tmp->next;
	}
	p.deleteBulletSPaceship(); //elimina i proiettili dalla lista di proiettili della navicella
	head1 = modificaLista1(p, head1, xx, yy);    //modfica la lista di Buker1 nel caso ci venga distrutto un bunker
	head2 = modificaLista2(p, head2, xx, yy);    //modfica la lista di Buker2 nel caso ci venga distrutto un bunker

	//un ulteriore controllo per vedere se un pianeta è stato completato (non ci sono piu bunker)
	if (assenzaBunker()) {  //booleano che restituisce true se non sono piu presenti nella scehrmata caratteri che rappresentano dei bunker
		while (head1 != NULL) {
			ptr_listaBunker1 tmp = head1;
			head1 = head1->next;
			delete tmp;
		}
		while (head2 != NULL) {
			ptr_listaBunker2 tmp = head2;
			head2 = head2->next;
			delete tmp;
		}
		//cancella tutti gli spari dei bunker
		for (int y = 0; y <= yMatrice; y++) {
			for (int x = 0; x <= xMatrice; x++) {
				if (matrice[x][y] == '.') matrice[x][y] = ' ';
			}
		}
	}
}


//restituisce se sono presenti o meno dei caratteri che rappresentano dei bunker
bool PlanetSurface::assenzaBunker() {
	bool guardia = true;
	for (int y = 0; y <= yMatrice; y++) {
		for (int x = 0; x <= 79; x++) {
			if ((matrice[x][y] == 'b') || (matrice[x][y] == 'B')) guardia = false;
		}
	}
	return guardia;
}


//controlla tutta la lista di Bunker1 e se trova un bunker con le vite azzerate compie diverse azioni
ptr_listaBunker1 PlanetSurface::modificaLista1(Spaceship & p, ptr_listaBunker1 & head, int x, int y) {
	if (head == NULL) return NULL;
	else if (head->b1->returnLife() < 1) {
		p.setScore(1);   //aggiorna il punteggio della navicella
		eliminareSpariBunker1Distrutto(head);  //elimina gli spari di entrambe le liste di proiettili (svuota la lista e li cancella graficamente)
		matrice[x][y] = ' ';                    //elimina il carattere rappresentante il bunker
		ptr_listaBunker1 tmp = head->next;
		delete head;                      //cancella il bunker dalla lista
		return modificaLista1(p, tmp, x, y);    //ricorsiva
	}
	else {
		head->next = modificaLista1(p, head->next, x, y);
		return head;
	}
}


//stesso ragionamento di modificaLista1, ma con i Bunker2
ptr_listaBunker2 PlanetSurface::modificaLista2(Spaceship & p, ptr_listaBunker2 & head, int x, int y) {
	if (head == NULL) return NULL;
	else if (head->b2->returnLife() < 1) {
		p.setScore(2);
		eliminareSpariBunker2Distrutto(head);
		matrice[x][y] = ' ';
		ptr_listaBunker2 tmp = head->next;
		delete head;
		return modificaLista2(p, tmp, x, y);
	}
	else {
		head->next = modificaLista2(p, head->next, x, y);
		return head;
	}
}


//metodo con il compito di azzerare le liste di proiettili e cancellarli graficamente 
void PlanetSurface::eliminareSpariBunker1Distrutto(ptr_listaBunker1 & head) {
	ptr_Bullet tmpSx = head->b1->returnLP(1)->retrunList();
	ptr_Bullet tmpDx = head->b1->returnLP(2)->retrunList();
	//primo ciclo con il quale assegna a tutti i proiettili il valore true al campo "eliminato" e li cancella graficamente 
	while (tmpSx != NULL) {
		matrice[tmpSx->xBullet][tmpSx->yBullet] = ' ';
		tmpSx->eliminato = true;
		tmpSx = tmpSx->next;
	}
	//primo ciclo con il quale assegna a tutti i proiettili il valore true al campo "eliminato" e li cancella graficamente 

	while (tmpDx != NULL) {
		matrice[tmpDx->xBullet][tmpDx->yBullet] = ' ';
		tmpDx->eliminato = true;
		tmpDx = tmpDx->next;
	}
	//secondo ciclo con il quale elimina tutti i proiettili ed azzera la lista di proiettili
	while (head->b1->returnLP(1)->retrunList() != NULL) head->b1->returnLP(1)->deleteBullets();
	while (head->b1->returnLP(2)->retrunList() != NULL) head->b1->returnLP(2)->deleteBullets();
}


//stesso ragionamento di modificaLista1, ma con i Bunker2
void PlanetSurface::eliminareSpariBunker2Distrutto(ptr_listaBunker2 & head) {
	ptr_Bullet tmpSx = head->b2->returnLP(1)->retrunList();
	ptr_Bullet tmpDx = head->b2->returnLP(2)->retrunList();
	ptr_Bullet tmpCentrale = head->b2->returnLP(3)->retrunList();
	while (tmpSx != NULL) {
		matrice[tmpSx->xBullet][tmpSx->yBullet] = ' ';
		tmpSx = tmpSx->next;
	}
	while (tmpCentrale != NULL) {
		matrice[tmpCentrale->xBullet][tmpCentrale->yBullet] = ' ';
		tmpCentrale = tmpCentrale->next;
	}
	while (tmpDx != NULL) {
		matrice[tmpDx->xBullet][tmpDx->yBullet] = ' ';
		tmpDx = tmpDx->next;
	}
	ptr_listaBunker2 tmp2 = head;
	while (tmp2 != NULL) {
		tmp2->b2->deleteAllBulletsBunker2();
		tmp2 = tmp2->next;
	}
}


//metodo per cancellare tutti i proiettili presenti in gioco, sia quelli della navicella che quelli di tutti i bunker
//una volta eseguito il suo compito imposta il booleano che lo attiva a falso, cosi che finche non si esce dal pianeta il metodo non venga piu utilizzato
//(viene poi rimpostato in true in una riga nel main una volta uscito dal pianeta)
//viene usato quando si esce dal pianeta per pulire la schermata
//usa il criterio gia visto nei metodi precenti
void PlanetSurface::azzerareListeBullets(Spaceship & p, bool& b) {
	if (b) {
		for (int y = 0; y <= yMatrice; y++) {
			for (int x = 0; x <= xMatrice; x++) {
				if ((matrice[x][y] == '.')|| (matrice[x][y] == ':')) matrice[x][y] = ' ';
			}
		}
		p.deleteAllBulletsSpaceship();
		ptr_listaBunker1 tmp1 = LBunker1;
		while (tmp1 != NULL) {
			tmp1->b1->deleteAllBulletsBunker1();
			tmp1 = tmp1->next;
		}
		ptr_listaBunker2 tmp2 = LBunker2;
		while (tmp2 != NULL) {
			tmp2->b2->deleteAllBulletsBunker2();
			tmp2 = tmp2->next;
		}
	}
	b = false;
}


//restituisce la lista di Bunker1
ptr_listaBunker1 PlanetSurface::ritornoBunkerList1() {
	return LBunker1;
}


//restituisce la lista di Bunker2
ptr_listaBunker2 PlanetSurface::ritornoBunkerList2() {
	return LBunker2;
}