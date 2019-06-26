#pragma once
class Mapp {
protected:
	int xMatrice = 100;
	int yMatrice = 20;
	char matrice[101][21]; //mappa
public:
	Mapp();
	void printMapp(int i = 0, int a = 0);
	void setMapp();
	void setInitialMapp();
	void setContinueMapp();
	void setFinalMapp();
	void setGeneralParameters(int fuel, int life);
	void setPlanetSurfaceParameters(int fuel, int life);
	void setSolarSystemParameters(int fuel, int life, int universo);
	void ShowConsoleCursor(bool showFlag);
};
