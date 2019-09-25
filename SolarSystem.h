#pragma once
#include "PlanetSurface.h"
#include "Mapp.h"
#include "Spaceship.h"
#include "Bunker1.h"
#include "Bunker2.h"


struct Planet {
	int xPlanet;
	int yPlanet;
	ptr_PlanetSurface planetSurface;  //puntatore all’oggetto PlanetSurface, dal quale poi si entra all’interno del pianeta
	ptr_listaBunker1 listBunker1;     //puntatore alla lista di Bunker1 (quando = a NULL insieme a listBunker2  ->  pianeta distrutto)
	ptr_listaBunker2 listBunker2;     //puntatore alla lista di Bunker2 (quando = a NULL insieme a listBunker1  ->  pianeta distrutto)
	Planet* next;
	Planet* prev;
};
typedef Planet* ptr_Planet;


//SS indica sistema solare
struct SS {
	int numberSolarSystem;
	ptr_Planet puntatore_planet;
	bool completed;
	SS* next;
	SS* prev;
};
typedef SS* ptr_SS;


class SolarSystem : public Mapp {
protected:
	ptr_SS SSystem;
public:
	SolarSystem(Spaceship p);
	void addSolarSystem(Spaceship p);
	ptr_Planet creaListaPianeti(Spaceship p, ptr_Planet head, int u);
	bool ifPianetiSovrapposti();
	void setMappUniverso(Spaceship p);
	char interationSpaceship(Spaceship& p, bool& b, int& numeroSS);
	ptr_PlanetSurface pianetaCorrente(Spaceship p, char n);
	void solarSystemDestroyed();
	void solarSystemChange(int i);
	bool returnIfDestroyed();
	void spostamentoUniverso(char& moveSpaceshipUniverso);
	void aggiornamentoListaBunker(Spaceship p, char n, ptr_listaBunker1 head1, ptr_listaBunker2 head2);
};
