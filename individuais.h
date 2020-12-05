/*
*	Peças individuais feitas em classes
*/
#ifndef IND_H_
#define IND_H_

#include <iostream>
#include <string>

#include "peca.h"
using namespace std;

class Peao: public Peca{
public:
	Peao(int, int, int);
	Peao(int x, int y);
	~Peao();
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};

class Torre : public Peca{
public:
	Torre(int, int, int);
	Torre(int x, int y);
	~Torre();
	static bool movimento_torre(Board &b, int x, int y, Peca &p);
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};


class Cavalo : public Peca{
public:
	Cavalo(int, int, int);
	Cavalo(int x, int y);
	~Cavalo();
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};

class Bispo : public Peca{
private:
	
public:
	Bispo(int cor, int x, int y);
	Bispo(int x, int y);
	~Bispo();
	static bool movimento_bispo(Board &b, int x, int y, Peca &p);
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};

class Rainha : public Peca{
public:
	Rainha(int cor, int x, int y);
	Rainha(int x, int y);
	~Rainha();
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};

class Rei : public Peca{
private:
	
public: 
	Rei(int cor, int x, int y);
	Rei(int x, int y);
	~Rei();
	virtual bool movimento_possivel(Board &b, int x, int y);
	virtual string getNotacao();
};

#endif