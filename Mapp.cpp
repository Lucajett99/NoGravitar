#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Mapp.h"
using namespace std;

//costruttore 
Mapp::Mapp() {
}


//metodo per stampare
//ogni refresh viene cancellato la schermata precedente
//metoto strutturato per non fare vedere il cursore e evitare di far evedere il refresh, cosi da avere una scehrmata piu fissa possibile
//vengono settati vari colori in base al carattere (che a loro volta costituiscono una componente diverse della schermata)
//inserito uno "Sleep" per diminuire il refresh
void Mapp::printMapp(int i, int a) {
	if (i == 1) setInitialMapp();
	else if (i == 2) setContinueMapp();
	else if (i == 3) setFinalMapp();
	system("cls");
	ShowConsoleCursor(false);
	const int WIDTH = 101;
	const int HEIGHT = 21;
	SMALL_RECT windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	COORD bufferSize = { WIDTH , HEIGHT };
	COORD characterBufferSize = { WIDTH , HEIGHT };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			consoleBuffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)matrice[x][y];
			if (a == 0) {
				if (((matrice[x][y] == 'Y') || (matrice[x][y] == ':')) && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_RED;
				else if ((matrice[x][y] == 'O') && (x < 78)) {
					if (i != 1) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_GREEN;
					else  consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
				}
				else if (((matrice[x][y] == '/') || (matrice[x][y] == 92) || (matrice[x][y] == 34)) && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_GREEN;
				else if ((matrice[x][y] == 'X') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE;
				else if ((matrice[x][y] == 'C') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = 14;
				else if ((matrice[x][y] == 'c') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = 14;
				else if ((matrice[x][y] == 'B') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_RED;
				else if ((matrice[x][y] == 'b') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = 12;
				else if ((matrice[x][y] == '|') && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = BACKGROUND_RED;
				else if ((matrice[x][y] == 34) && (x < 78)) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_GREEN;
				else consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
			}
			else if (a == 1) consoleBuffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		}
	}
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	Sleep(50);
}


//metodo per settare la cornice della mappa (schermata), che sarà poi fissa perchè uguale in tutte le varie situazioni del gioco
//impostato il tutto con una matrice
//settati i vari bordi di delimitazione e al loro interno rimpito con caratteri vuoti
void Mapp::setMapp() {
	for (int y = 0; y <= yMatrice; y++) {
		for (int x = 0; x <= xMatrice; x++) {
			matrice[x][y] = ' ';
		}
	}
	matrice[0][0] = 201;
	matrice[0][20] = 200;
	matrice[100][0] = 187;
	matrice[100][20] = 188;
	int i;
	for (i = 1; i < yMatrice; i++)  matrice[0][i] = 186;
	for (i = 1; i < yMatrice; i++)  matrice[xMatrice][i] = 186;
	for (i = 1; i < xMatrice; i++)  matrice[i][0] = 205;
	for (i = 1; i < xMatrice; i++)  matrice[i][yMatrice] = 205;
	for (i = 1; i < yMatrice; i++)  matrice[78][i] = 186;
	for (i = 79; i < 100; i++) matrice[i][7] = 205;
	matrice[78][7] = 204;
	matrice[100][7] = 185;
	matrice[78][0] = 203;
	matrice[78][20] = 202;
}


//metodo usato per settare nella matrice generale le informazioni generali che sono sempre presenti
//ci sono le informazioni fisse, ovvero i comandi generali (le freccie direzionali)
//ci sono le informazioni variabili, ovvero i vari parametri del gioco (carburante, vita e punteggio)
void Mapp::setGeneralParameters(int fuel, int life, int score) {
	int lifeDecine = (life / 10);
	int lifeUnità = (life - (lifeDecine * 10));
	
	int fuelMigliaia = (fuel / 1000);
	int fuelCentinaia = ((fuel - (fuelMigliaia * 1000)) / 100);
	int fuelDecine = ((fuel - (fuelMigliaia * 1000) - (fuelCentinaia * 100)) / 10);
	int fuelUnità = (fuel - (fuelMigliaia * 1000) - (fuelCentinaia * 100) - (fuelDecine * 10));

	int scoreCentoMilioni =  (score / 100000000);
	int scoreDieciMilioni =  ((score - (scoreCentoMilioni * 100000000)) / 10000000);
	int scoreMilione =       ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000)) / 1000000);
	int scoreCentoMigliaia = ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000)) / 100000);
	int scoreDieciMigliaia = ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000) - (scoreCentoMigliaia * 100000)) / 10000);
	int scoreMigliaia =      ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000) - (scoreCentoMigliaia * 100000) - (scoreDieciMigliaia * 10000)) / 1000);
	int scoreCentinaia =     ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000) - (scoreCentoMigliaia * 100000) - (scoreDieciMigliaia * 10000) - (scoreMigliaia * 1000)) / 100);
	int scoreDecine =        ((score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000) - (scoreCentoMigliaia * 100000) - (scoreDieciMigliaia * 10000) - (scoreMigliaia * 1000) - (scoreCentinaia * 100)) / 10);
	int scoreUnità =          (score - (scoreCentoMilioni * 100000000) - (scoreDieciMilioni * 10000000) - (scoreMilione * 1000000) - (scoreCentoMigliaia * 100000) - (scoreDieciMigliaia * 10000) - (scoreMigliaia * 1000) - (scoreCentinaia * 100) - (scoreDecine * 10));

	matrice[79][1] = 'V';
	matrice[80][1] = 'I';
	matrice[81][1] = 'T';
	matrice[82][1] = 'A';
	matrice[83][1] = ':';
	matrice[84][1] = (char)lifeDecine + 48;
	matrice[85][1] = (char)lifeUnità + 48;

	matrice[79][2] = 'C';
	matrice[80][2] = 'A';
	matrice[81][2] = 'R';
	matrice[82][2] = 'B';
	matrice[83][2] = 'U';
	matrice[84][2] = 'R';
	matrice[85][2] = 'A';
	matrice[86][2] = 'N';
	matrice[87][2] = 'T';
	matrice[88][2] = 'E';
	matrice[89][2] = ':';
	matrice[90][2] = (char)fuelMigliaia + 48;
	matrice[91][2] = (char)fuelCentinaia + 48;
	matrice[92][2] = (char)fuelDecine + 48;
	matrice[93][2] = (char)fuelUnità + 48;

	matrice[79][3] = 'P';
	matrice[80][3] = 'U';
	matrice[81][3] = 'N';
	matrice[82][3] = 'T';
	matrice[83][3] = 'E';
	matrice[84][3] = 'G';
	matrice[85][3] = 'G';
	matrice[86][3] = 'I';
	matrice[87][3] = 'O';
	matrice[88][3] = ':';
	if (score < 100000000) matrice[89][3] = 48;
	else matrice[89][3] = (char)scoreCentoMilioni + 48;
	if (score < 10000000) matrice[90][3] = 48;
	else matrice[90][3] = (char)scoreDieciMilioni + 48;
	if (score < 1000000) matrice[91][3] = 48;
	else matrice[91][3] = (char)scoreMilione + 48;
	if (score < 100000) matrice[92][3] = 48;
	else matrice[92][3] = (char)scoreCentoMigliaia + 48;
	if (score < 10000) matrice[93][3] = 48;
	else matrice[93][3] = (char)scoreDieciMigliaia + 48;
	if (score < 1000) matrice[94][3] = 48;
	else matrice[94][3] = (char)scoreMigliaia + 48;
	if (score < 100) matrice[95][3] = 48;
	else matrice[95][3] = (char)scoreCentinaia + 48;
	if (score < 10) matrice[96][3] = 48;
	else matrice[96][3] = (char)scoreDecine + 48;
	matrice[97][3] = (char)scoreUnità + 48;


	matrice[86][8] = 'C';
	matrice[87][8] = 'O';
	matrice[88][8] = 'M';
	matrice[89][8] = 'A';
	matrice[90][8] = 'N';
	matrice[91][8] = 'D';
	matrice[92][8] = 'I';


	matrice[89][14] = '^';
	matrice[86][12] = 'F';
	matrice[87][12] = 'R';
	matrice[88][12] = 'E';
	matrice[89][12] = 'C';
	matrice[90][12] = 'C';
	matrice[91][12] = 'I';
	matrice[92][12] = 'A';
	matrice[88][13] = 'S';
	matrice[89][13] = 'U';

	matrice[89][16] = 'v';
	matrice[86][17] = 'F';
	matrice[87][17] = 'R';
	matrice[88][17] = 'E';
	matrice[89][17] = 'C';
	matrice[90][17] = 'C';
	matrice[91][17] = 'I';
	matrice[92][17] = 'A';
	matrice[88][18] = 'G';
	matrice[89][18] = 'I';
	matrice[90][18] = 'U';

	matrice[87][15] = '<';
	matrice[79][15] = 'F';
	matrice[80][15] = 'R';
	matrice[81][15] = 'E';
	matrice[82][15] = 'C';
	matrice[83][15] = 'C';
	matrice[84][15] = 'I';
	matrice[85][15] = 'A';
	matrice[81][16] = 'S';
	matrice[82][16] = 'X';

	matrice[91][15] = '>';
	matrice[93][15] = 'F';
	matrice[94][15] = 'R';
	matrice[95][15] = 'E';
	matrice[96][15] = 'C';
	matrice[97][15] = 'C';
	matrice[98][15] = 'I';
	matrice[99][15] = 'A';
	matrice[95][16] = 'D';
	matrice[96][16] = 'X';
}


//metodo per settare il numero del sistema solare (informazione presente solo nella schermata del sistema solare)
//aggiunge alle informazioni generali quella del sistema solare in cui si è
void Mapp::setSolarSystemParameters(int fuel, int life, int score, int universo) {
	setGeneralParameters(fuel, life, score);

	matrice[81][5] = 'S';
	matrice[82][5] = 'I';
	matrice[83][5] = 'S';
	matrice[84][5] = 'T';
	matrice[85][5] = 'E';
	matrice[86][5] = 'M';
	matrice[87][5] = 'A';
	matrice[88][5] = ' ';
	matrice[89][5] = 'S';
	matrice[90][5] = 'O';
	matrice[91][5] = 'L';
	matrice[92][5] = 'A';
	matrice[93][5] = 'R';
	matrice[94][5] = 'E';
	matrice[95][5] = ':';
	matrice[96][5] = (char)universo + 48;
}


//metodo per settare le informazioni relative ai comandi di gioco all'interno del pianeta (come sparare e attivare il raggio traente)
//aggiunge alle informazioni generali i comandi all'interno del pianeta
void Mapp::setPlanetSurfaceParameters(int fuel, int life, int score) {
	setGeneralParameters(fuel, life, score);

	matrice[79][9] = 'q';
	matrice[80][9] = ' ';
	matrice[81][9] = ':';
	matrice[82][9] = ' ';
	matrice[83][9] = 'A';
	matrice[84][9] = 'T';
	matrice[85][9] = 'T';
	matrice[86][9] = 'I';
	matrice[87][9] = 'V';
	matrice[88][9] = 'A';
	matrice[89][9] = 'R';
	matrice[90][9] = 'E';
	matrice[91][9] = ' ';
	matrice[92][9] = 'R';
	matrice[93][9] = 'A';
	matrice[94][9] = 'G';
	matrice[95][9] = 'G';
	matrice[96][9] = 'I';
	matrice[97][9] = 'O';

	matrice[79][10] = 's';
	matrice[80][10] = 'p';
	matrice[81][10] = 'a';
	matrice[82][10] = 'c';
	matrice[83][10] = 'e';
	matrice[84][10] = ' ';
	matrice[85][10] = ':';
	matrice[86][10] = ' ';
	matrice[87][10] = 'S';
	matrice[88][10] = 'P';
	matrice[89][10] = 'A';
	matrice[90][10] = 'R';
	matrice[91][10] = 'A';
	matrice[92][10] = 'R';
	matrice[93][10] = 'E';
}


//metodo per impostare la schermata iniziale, la schermata con le informazioni di inizio gioco
void Mapp::setInitialMapp() {
	for (int y = 0; y <= yMatrice; y++) {
		for (int x = 0; x <= xMatrice; x++) {
			matrice[x][y] = ' ';
		}
	}
	matrice[0][0] = 201;
	matrice[0][20] = 200;
	matrice[100][0] = 187;
	matrice[100][20] = 188;
	int i;
	for (i = 1; i < yMatrice; i++)  matrice[0][i] = 186;
	for (i = 1; i < yMatrice; i++)  matrice[xMatrice][i] = 186;
	for (i = 1; i < xMatrice; i++)  matrice[i][0] = 205;
	for (i = 1; i < xMatrice; i++)  matrice[i][yMatrice] = 205;

	matrice[48][9] = 'N';
	matrice[49][9] = 'O';
	matrice[50][9] = ' ';
	matrice[51][9] = 'G';
	matrice[52][9] = 'R';
	matrice[53][9] = 'A';
	matrice[54][9] = 'V';
	matrice[55][9] = 'I';
	matrice[56][9] = 'T';
	matrice[57][9] = 'A';
	matrice[58][9] = 'R';

	matrice[44][10] = 'P';
	matrice[45][10] = 'r';
	matrice[46][10] = 'e';
	matrice[47][10] = 'm';
	matrice[48][10] = 'e';
	matrice[49][10] = 'r';
	matrice[50][10] = 'e';
	matrice[51][10] = ' ';
	matrice[52][10] = 't';
	matrice[53][10] = 'a';
	matrice[54][10] = 's';
	matrice[55][10] = 't';
	matrice[56][10] = 'o';
	matrice[57][10] = ' ';
	matrice[58][10] = 'i';
	matrice[59][10] = 'n';
	matrice[60][10] = 'v';
	matrice[61][10] = 'i';
	matrice[62][10] = 'o';
}



//metodo per impostare la schermata di fine gioco 
void Mapp::setFinalMapp() {
	for (int y = 0; y <= yMatrice; y++) {
		for (int x = 0; x <= xMatrice; x++) {
			matrice[x][y] = ' ';
		}
	}
	matrice[0][0] = 201;
	matrice[0][20] = 200;
	matrice[100][0] = 187;
	matrice[100][20] = 188;
	int i;
	for (i = 1; i < yMatrice; i++)  matrice[0][i] = 186;
	for (i = 1; i < yMatrice; i++)  matrice[xMatrice][i] = 186;
	for (i = 1; i < xMatrice; i++)  matrice[i][0] = 205;
	for (i = 1; i < xMatrice; i++)  matrice[i][yMatrice] = 205;

	matrice[45][9] = 'G';
	matrice[46][9] = 'A';
	matrice[47][9] = 'M';
	matrice[48][9] = 'E';
	matrice[49][9] = ' ';
	matrice[50][9] = '0';
	matrice[51][9] = 'V';
	matrice[52][9] = 'E';
	matrice[53][9] = 'R';
}


//metodo per impostare la schermata una volta che si è finita la vita
//propone due scelte: quella di terminare il gioco oppure quella di ricominciarlo da capo
void Mapp::setContinueMapp() {
	setFinalMapp();

	matrice[38][10] = 'D';
	matrice[39][10] = 'o';
	matrice[40][10] = ' ';
	matrice[41][10] = 'y';
	matrice[42][10] = 'o';
	matrice[43][10] = 'u';
	matrice[44][10] = ' ';
	matrice[45][10] = 'w';
	matrice[46][10] = 'a';
	matrice[47][10] = 'n';
	matrice[48][10] = 't';
	matrice[49][10] = ' ';
	matrice[50][10] = 't';
	matrice[51][10] = 'o';
	matrice[52][10] = ' ';
	matrice[53][10] = 'r';
	matrice[54][10] = 'e';
	matrice[55][10] = 's';
	matrice[56][10] = 't';
	matrice[57][10] = 'a';
	matrice[58][10] = 'r';
	matrice[59][10] = 't';
	matrice[61][10] = '?';

	matrice[37][13] = 'Y';
	matrice[38][13] = 'E';
	matrice[39][13] = 'S';
	matrice[35][14] = 'P';
	matrice[36][14] = 'r';
	matrice[37][14] = 'e';
	matrice[38][14] = 's';
	matrice[39][14] = 's';
	matrice[40][14] = ':';
	matrice[41][14] = 'y';

	matrice[57][13] = 'N';
	matrice[58][13] = 'O';
	matrice[55][14] = 'P';
	matrice[56][14] = 'r';
	matrice[57][14] = 'e';
	matrice[58][14] = 's';
	matrice[59][14] = 's';
	matrice[60][14] = ':';
	matrice[61][14] = 'n';
}


//metodo per non mostrare il cursore nella schermata
void Mapp::ShowConsoleCursor(bool showFlag) {  
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}