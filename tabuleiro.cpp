#include "tabuleiro.h"

Board::Board(string a){
	//Monta BRANCOS
	endofgame = false;
	Torre *t1 = new Torre(1,7,0), *t2 = new Torre(1,7,7);
	Cavalo *cv1 = new Cavalo(1,7,1), *cv2 = new Cavalo(1,7,6);
	Bispo *b1 = new Bispo(1,7,2), *b2 = new Bispo(1,7,5);
	Rainha *qn = new Rainha(1,7,3);
	Rei *kn = new Rei(1,7,4);
	for(int i=0; i<8;i++){
		Peao *p = new Peao(1,6,i);
		tab[6][i] = p;
	}
	reibranco = kn;
	tab[7][0] = t1;
	tab[7][1] = cv1;
	tab[7][2] = b1;
	tab[7][3] = qn;
	tab[7][4] = kn;
	tab[7][5] = b2;
	tab[7][6] = cv2;
	tab[7][7] = t2;

	//Monta PRETOS
	Torre *t3 = new Torre(0,0), *t4 = new Torre(0,7);
	Cavalo *cv3 = new Cavalo(0,1), *cv4 = new Cavalo(0,6);
	Bispo *b3 = new Bispo(0,2), *b4 = new Bispo(0,5);
	Rainha *qn2 = new Rainha(0,3);
 	Rei *kn2 = new Rei(0,4);
 	for (int i=0; i<8; i++){
 		Peao *p2 = new Peao(1,i);
 		tab[1][i] = p2;
 	}
 	reipreto = kn2;
	tab[0][0] = t3;
	tab[0][1] = cv3;
	tab[0][2] = b3;
	tab[0][3] = qn2;
	tab[0][4] = kn2;
	tab[0][5] = b4;
	tab[0][6] = cv4;
	tab[0][7] = t4;

	//Seta os espaços vazios do tabuleiro
	for (int i=0; i<8; i++){
		tab[2][i] = NULL;
		tab[3][i] = NULL;
		tab[4][i] = NULL;
		tab[5][i] = NULL;
	}
}

Board::~Board(){
	Peca *del;
	for (int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(tab[i][j] != NULL){
				del = tab[i][j];
				delete del;
				tab[i][j] = NULL;
			}
		}
	}
	reipreto = NULL;
	reibranco = NULL;
	endofgame = true;
}

bool Board::getState(){
	return endofgame;
}

void Board::setState(bool state){
	endofgame = state;
}

Peca * Board::getPeca(int X, int Y){
	return tab[X][Y];
}

void Board::setPeca(int X, int Y, Peca *p){
	tab[X][Y] = p;
}

void Board::printBoard(){
	cout << "     a   b   c   d   e   f   g   h" << endl;
	for (int i = 0; i<8; i++){
		cout << " " << 9-i-1 << " ";
		for (int j=0; j<8;j++){
			if (tab[i][j]==NULL)
				cout << "|   ";
			else
				cout << "| " << tab[i][j]->getNome() << " ";
		}
		cout << "|" << endl;
	}
}

void Board::setRei(int cor){
	if(cor == 1) reibranco = NULL;
	else if (cor == 2) reipreto = NULL;
}

Peca * Board::getRei(int cor){
	if (cor==1)
		return reibranco;
	else return reipreto;
}

bool Board::check_xeque(int cor){ //cor do rei
    Peca *rei = getRei(cor);
    for(int i=0;i<8;i++){
        for(int j=0; j<8;j++){
            if(tab[i][j]!= NULL){
                if(tab[i][j]->getCor() != cor) {
                    if(tab[i][j]->movimento_possivel(*this,rei->getPosicaoX(),rei->getPosicaoY())) {
                        std::cerr << "\033[0;31m" << i << ' ' << j << "\033[0m" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::escreve_arquivo(ofstream &arquivo, int x, int y, int flag){
	Peca *p = getPeca(x,y);
	x++;
	x = std::abs(9-x);
	y = y + 'a';
	if(flag == -1)
		arquivo << p->getNotacao()  << "x" << char(y) << x;
	else
		arquivo << p->getNotacao() << char(y) << x;
	return true;
}

Peca * Board::encontra_possivel(string tipo, int x, int y, int cor){
	if (tipo == "P") tipo = "";
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			if(tab[i][j] != NULL){
				if(tab[i][j]->getNotacao() == tipo){
					if(tab[i][j]->getCor() == cor){
						if(tab[i][j]->movimento_possivel(*this,x,y)) {
                        	return tab[i][j];
                    	}
					}
				}
			}
		}
	}
	return NULL;
}