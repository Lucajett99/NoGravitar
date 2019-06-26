#pragma once
#include "Mapp.h"
#include "Spaceship.h"
#include "Bunker1.h"
#include "Bunker2.h"
#include "Bullets.h"



class PlanetSurface : public Mapp {
protected:
	ptr_listaBunker1 LBunker1;
	ptr_listaBunker2 LBunker2;
public:
	PlanetSurface(Spaceship spaceship, ptr_listaBunker1& head, ptr_listaBunker2& head2);
	void setMappPlanetSurface(Spaceship& p, char n, bool& b);
	char interationSpaceshipPlanetSurface(Spaceship& p, bool& pianetaDistrutto);
	void raggioTraenteUscente(Spaceship& p);
	void raggioTraenteEntrante(Spaceship p);
	ptr_listaBunker1 creaBunkerList1(ptr_listaBunker1 head, int xB, int yB);
	ptr_listaBunker2 creaBunkerList2(ptr_listaBunker2 head, int xB, int yB);
	void spostamentoPlaetSurface(char& moveSpaceshipUniverso);

	ptr_listaBunker1&  ritornoBunkerList1();
	ptr_listaBunker2&  ritornoBunkerList2();
	void azzerareListeBullets(Spaceship& p, bool& b);

	char ritornaValoreMappa(int x, int y);
	void impostaMappa(int x, int y, char c);

	void refreshBunker(Spaceship& p);
	void spariBunker();

};
typedef class PlanetSurface* ptr_PlanetSurface;