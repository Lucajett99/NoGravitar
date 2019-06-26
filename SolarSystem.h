#pragma once
#include "PlanetSurface.h"
#include "Mapp.h"
#include "Spaceship.h"
#include "Bunker1.h"
#include "Bunker2.h"


struct Planet {
	int numberPlanet;
	int xPlanet;
	int yPlanet;
	ptr_PlanetSurface planetSurface;
	ptr_listaBunker1 listBunker1;
	ptr_listaBunker2 listBunker2;
	Planet* next;
	Planet* prev;
};
typedef Planet* ptr_Planet;

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
	void setMappUniverso(Spaceship p);
	char interationSpaceship(Spaceship& p, bool& b, int& numeroSS);
	ptr_PlanetSurface pianetaCor(Spaceship p, char n);
	void solarSystemDestroyed();
	void solarSystemChange(int i);
	bool returnIfDestroyed();
	void spostamentoUniverso(char& moveSpaceshipUniverso);
	void xxx(Spaceship p, char n, ptr_listaBunker1 head1, ptr_listaBunker2 head2);
};
