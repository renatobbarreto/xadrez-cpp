#ifndef TABULEIRO_H
#define TABULEIRO_H

/*
 *	Tabuleiro do jogo de Xadrez
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "peca.h"
#include "individuais.h"

class Board{
private:
	Peca* tab[8][8];
	Peca* reibranco;
	Peca* reipreto;
	bool endofgame;
public:
	/* Seta o tabuleiro do jogo com as peças padrão 
	 * Definindo a cor e a localização de cada uma no tabuleiro
	 * Brancos tem as posições de A1 a H2
	 * Pretos tem as posições de  A7 a H8*/
	
	Board(string a);

	bool getState();

	void setState(bool state);

	Peca * getPeca(int X, int Y);

	Peca * getRei(int cor);

	void setRei(int cor);

	bool check_xeque(int cor);

	void setPeca(int X, int Y, Peca *p);

	~Board();

	void printBoard();

	bool escreve_arquivo(ofstream &arquivo, int x, int y, int flag);

	Peca * encontra_possivel(string tipo, int x, int y, int cor);
};

#endif