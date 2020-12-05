#include "peca.h"
#include "tabuleiro.h"


Peca::Peca(int color, int lin, int col, string name){
	cor = color;
	_x = lin;
	_y = col;
	_name = name;
}

Peca::~Peca(){}


int Peca::getCor(){
	return cor;
}
	
void Peca::setCor(int c){
	cor = (c >= 0 || c <= 1)? c : -1;
}
	
void Peca::setPosicao(int x, int y){
	_x = x;
	_y = y;
}

int Peca::getPosicaoX(){
	return _x;
}

int Peca::getPosicaoY(){
	return _y;
}

string Peca::getNome(){
	return _name;
}

int Peca::efetua_movimento(Board &b, int x, int y){
	int flag = 1;
	if(b.getPeca(x,y)!=NULL){ // Entra se o movimento for retirada de peças do tabuleiro
		Peca *del = b.getPeca(x,y);
		if (del->getNotacao() == "R"){
			b.setRei(del->getCor());
			b.setState(true);
		}
		delete del;
		flag = -1;
	}
	b.setPeca(x,y,this); 	 // seta o ponteiro para o tabuleiro
	b.setPeca(_x,_y,NULL);	 // seta a antiga posição para NULL
	this->setPosicao(x,y);
	return flag;
}