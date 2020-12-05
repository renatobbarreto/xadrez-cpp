#ifndef _PECA_H
#define _PECA_H

/*
 * Define o tipo classe Peça com suas características
 */

class Board;

#include <iostream>
//#include "tabuleiro.h"
//#include "individuais.h"
using namespace std;

class Peca {
private:
	string _name;
	int cor; 	 // def.: 1 para BRANCO 2 para PRETO
	int _x;		 // posição na linha do tabuleiro
	int _y;		 // posição na coluna do tabuleiro
public:
	Peca(int color, int lin, int col, string name);
	~Peca();
	int getCor();
	void setCor(int c);
	void setPosicao(int x, int y);
	int getPosicaoX();
	int getPosicaoY();
	string getNome();

	virtual bool movimento_possivel(Board &b, int x, int y) = 0;

	virtual string getNotacao() = 0;

	int efetua_movimento(Board &b, int x, int y);
};

#endif