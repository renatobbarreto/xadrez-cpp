#include "tabuleiro.h"
#include "individuais.h"

Peao::Peao(int cor, int x, int y) : Peca(cor, x, y, "\u265F"){

}

Peao::Peao(int x, int y) : Peca(2,x,y,"\u2659"){

}

Peao::~Peao(){}

/*char black[6] = { '\u265F', '\u265C', '\u265E', '\u265D', '\u265B', '\u265A' };
  char white[6] = { '\u2659', '\u2656', '\u2658', '\u2657', '\u2655', '\u2654' };*/

bool Peao::movimento_possivel(Board &b, int x, int y){
	if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
        
    int px = getPosicaoX(), py = getPosicaoY();
	int compara = std::abs(px - x);
    if(compara!= 2 && compara!=1) return false; // verificando se o deslocamento eh valido
    if(py == y){//peao nao movimenta em outro sentido a nao ser se for pra comer

    	if(b.getPeca(x,y)!=NULL) return false; // verificando se a posicao que ele deseja estah livre ou nao

    	if(getCor()==2)
        {
        	if(compara==2){
            	if(px!=1 || b.getPeca(px+1,py)!= NULL ) return false; //os peoes pretos comecam na linha 1, entao eles soh podem andar duas casas se estiverem em suas posicoes iniciais. A outra comparacao valida se ha uma peca no meio do caminho da posicao atual para a desejada, pois o peao nao pula peca.
        	}
        	return px < x; // se a posicao atual eh menor que a posicao desejada quer dizer que ele esta movimentando na direcao correta.

    	}else{
       		if(compara==2){
            	if(px != 6 || b.getPeca(px-1,py)!= NULL ) return false; //os peoes brancos comecam na linha 6, entao eles soh podem andar duas casas se estiverem em suas posicoes iniciais.  A outra comparacao valida se ha uma peca no meio do caminho da posicao atual para a desejada, pois o peao nao pula peca.
                	}
                return px > x;
        }

    }else{
        int comparacao_x = std::abs(px - x);
        int comparacao_y = std::abs(py - y);

        if(comparacao_x!=1 || comparacao_y!=1) return false; //se o peao vai comer uma outra peca, ele soh pode comer a peca da sua diagonal.

        if(b.getPeca(x,y)!=NULL) return true;
        }
        return false;
}

string Peao::getNotacao(){
    return "";
}

Torre::Torre(int cor, int x, int y) : Peca(cor, x, y, "\u265C") {}
Torre::Torre(int x, int y) : Peca(2,x,y,"\u2656"){}
Torre::~Torre(){}

bool Torre::movimento_torre(Board &b, int x, int y, Peca &p){
    if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == p.getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
        
	int px = p.getPosicaoX(), py = p.getPosicaoY();
	if(px == x) {// movimento horizontal
        int diferenca= std::abs(py - y);
        if(py > y){ // verificando se a torre vai para a esquerda ou para direita
            //movimento para esquerda
            for(int i=1; i< diferenca ; i++){
                if(b.getPeca(x,py-i) != NULL) return false;
                }
                return true;
        }else{
        //movimento para direita
            for(int i=1; i< diferenca ; i++){
        	    if(b.getPeca(x,py+i) != NULL) return false;
            }
        }
        return true;
    }
    if(py == y){ // movimento vertical
        int diferenca = abs(px - x);
        if (px > x){
        	//movimento para cima
            for(int i= 1 ; i < diferenca ; i++ ){
            	if(b.getPeca(px-i,y) != NULL) return false;
            }
    	}else{
            //movimento para baixo
            for(int i= 1 ; i < diferenca ; i++ ){
                if(b.getPeca(px+i,y) != NULL) return false;
                }
            }
            return true;
        }
        return false;
}


bool Torre::movimento_possivel(Board &b, int x, int y){
	return movimento_torre(b, x, y, *this);
}

string Torre::getNotacao(){
    return "T";
}

Cavalo::Cavalo(int cor, int x, int y): Peca(cor, x, y, "\u265E"){}
Cavalo::Cavalo(int x, int y) : Peca(2,x,y,"\u2658"){}
Cavalo::~Cavalo(){}

bool Cavalo::movimento_possivel(Board &b, int x, int y){
    if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
    
    int comparax = std::abs(getPosicaoX() - x);
	int comparay = std::abs(getPosicaoY() - y);
	//se o minimo de comparax com comparay eh igual a 1 e maximo 2, ou seja, a posicao eh valida pois ele so anda em "L"
	if(std::min(comparax, comparay) == 1 && std::max(comparax, comparay) == 2) {
        return true;
    }
}

string Cavalo::getNotacao(){
    return "C";
}

Bispo::Bispo(int cor, int x, int y): Peca(cor, x, y, "\u265D"){}
Bispo::Bispo(int x, int y) : Peca(2, x, y,"\u2657"){}
Bispo::~Bispo(){}

bool Bispo::movimento_bispo(Board &b, int x, int y, Peca &p){
    if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == p.getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
            
	int px = p.getPosicaoX(), py = p.getPosicaoY();
	if((px - py) != (x - y) && (px + py) != (x + y)){
        return false;
    } 

    int diferenca = std::abs(px - x);
    if(px > x && py < y) {//diagonal para direita superior
        for(int i=1; i < diferenca ; i++){
            if(b.getPeca(px-i,py+i) != NULL){ 
                return false;
            }
        }
        return true;
    }

    if(px > x && py > y) {//diagonal para esquerda superior
        for(int i=1; i < diferenca ; i++){
	        if(b.getPeca(px-i,py-i) != NULL){
                return false;
            }
        }
        return true;
    }

    if(px < x && py < y) {//diagonal para direita inferior
        for(int i=1; i < diferenca ; i++){
            if(b.getPeca(px+i,py+i)!=NULL){
                return false;
            }
        }
        return true;
    }

    if(px < x && py > y) {//diagonal para esquerda inferior
    	for(int i=1; i < diferenca ; i++){
            if(b.getPeca(px+i,py-i)!=NULL){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Bispo::movimento_possivel(Board &b, int x, int y){
	return movimento_bispo(b, x, y, *this);
}

string Bispo::getNotacao(){
    return "B";
}

Rainha::Rainha(int cor, int x, int y): Peca(cor, x, y, "\u265B"){}
Rainha::Rainha(int x, int y) : Peca(2, x, y, "\u2655"){}
Rainha::~Rainha(){}

bool Rainha::movimento_possivel(Board &b, int x, int y){
    if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
    
	bool verifica_horizontal = Torre::movimento_torre(b,x,y,*this);
	bool verifica_vertical = Bispo::movimento_bispo(b,x,y, *this);
	//se ela nao andar em diagonal ou em movimento de torre, nao caracteriza movimento da rainha
	if(!verifica_horizontal && !verifica_vertical) return false; 
		return true;
}

string Rainha::getNotacao(){
    return "D";
}

Rei::Rei(int cor, int x, int y): Peca(cor, x, y, "\u265A"){}
Rei::Rei(int x, int y) : Peca(2, x, y, "\u2654"){}
Rei::~Rei(){}

bool Rei::movimento_possivel(Board &b, int x, int y){
    if(b.getPeca(x,y) != NULL)
        if((b.getPeca(x,y)->getCor() == getCor()))  
            return false; // se for comer peça do mesmo time, retorna erro
    
	int compara_x= std::abs(getPosicaoX() - x);
    int compara_y= std::abs(getPosicaoY() - y);

    if(compara_x>1 || compara_y>1) return false; //verificando o movimento se eh valido
    if(b.getPeca(x,y)!=NULL) {

        if(b.getPeca(x,y)->getNotacao() == "R"){
            std::cout<<"OPA, Um rei nao pode matar outro rei "<< std::endl;
            return false;
        }
    }
    return true;
}

string Rei::getNotacao(){
    return "R";
}
