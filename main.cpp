#include <iostream>
#include <string>
#include <fstream>

#include "tabuleiro.h"
#include "individuais.h"
#include "peca.h"

using namespace std;

int traduz (int *x, char y){
	*x = std::abs(9-*x)-1;
	return int(y - 'a');
}

char traduz (string texto, int *x, int *y){
	int tam = texto.length();
	if(tam == 2){ //movimento de peão
		*y = int(texto[0] - 'a');
		*x = int(texto[1]-48);
		*x = std::abs(*x - 9)-1;
		return 'P';
	}
	else if(tam == 3){
		if(texto[0] == 'x'){
			*y = int(texto[1] - 'a');
			*x = int(texto[2]-48);
			*x = std::abs(*x - 9)-1;
			return 'P';
		} else {
			*y = int(texto[1] - 'a');
			*x = int(texto[2]-48);
			*x = std::abs(*x - 9)-1;
			return texto[0];
		}
	} else if (tam == 4){
		if(texto[1] == 'x'){
			*y = int(texto[2] - 'a');
			*x = int(texto[3]-48);
			*x = std::abs(*x - 9)-1;
			return texto[0];
		} else {
			*y = int(texto[1] - 'a');
			*x = int(texto[2]-48);
			*x = std::abs(*x - 9)-1;
			return texto[0];
		}
	} else{
		if(texto[1] == 'x'){
			*y = int(texto[2] - 'a');
			*x = int(texto[3]-48);
			*x = std::abs(*x - 9)-1;
			return texto[0];
		} else {
			*y = int(texto[1] - 'a');
			*x = int(texto[2]-48);
			*x = std::abs(*x - 9)-1;
			return texto[0];
		}
	}
}

int menu (void){
	std::cout << "Escolha uma opção de programa: \n<1> para jogo com 2 jogadores. \n<2> para ler um jogo pronto de um arquivo." << endl;
	std::cout << "opção: ";
	int in;
	std::cin >> in;
	return in;
}

int main(){
	std::cout <<"\n          Bem vindo ao Jogo de Xadrez!!" << endl << endl;
	ofstream jogadas_arq("jogadas.txt", ios::out);
	if (!jogadas_arq) cout << "WTF" << endl;
	int escolha = menu();
	string start;
	if(escolha == 1){
		cout << "Opção de jogo com dois jogadores!" << endl;
		cout << "Jogador 1 é o time branco e o jogador 2, time preto.\nAo ver o seu nome, selecione a peça desejada no formato LETRA NUMERO." <<  endl;
		cout << "por ex.: b 7    em seguida a peça selecionada aparecerá no formato \u265F  e então o jogo espera o destino da peça." << endl;
		cout << "Jogadas fora das regras não são permitidas!" << endl << "Podemos começar? <y/n>" << endl;
		cin >> start;
		if(start == "n") return 0;
		Board b(start);
		b.printBoard();
		Peca *p;
		char letra;
		int x, y, contador = 1, jog = 1;
		while (!b.getState()){
			jogadas_arq << contador << ". ";
			while(jog == 1){
				cout << "Jogador 1 escolha uma peça: ";
				cin >> letra >> x;
				y = traduz(&x, letra);
				p = b.getPeca(x,y);
				if(p == NULL || p->getCor() == 2){
					cout << "Peça invalida" << endl;
				}else{
					cout << " " << p->getNome() << "  mover para: ";
					cin >> letra >> x;
					y = traduz(&x, letra);
					if(p->movimento_possivel(b,x,y)){
						if(p->efetua_movimento(b,x,y) == 1)
							b.escreve_arquivo(jogadas_arq, x, y, 1);
						else
							b.escreve_arquivo(jogadas_arq, x, y, -1);
						jog = 2;
					}
					else
						cout << "Movimento falhou!" << endl;
					b.printBoard();
				}
				if(b.getState()) break;
				if(b.check_xeque(2)){
		            std::cout<<" Rei Preto Esta em Cheque" << std::endl;
		           	jogadas_arq << "+";
		        }
			}
			if(b.getState()) break;
			jogadas_arq << " ";
			while (jog == 2){
				cout << "Jogador 2 escolha uma peça: ";
				cin >> letra >> x;
				y = traduz(&x, letra);
				p = b.getPeca(x,y);
				if(p == NULL || p->getCor() == 1){
					cout << "Peça invalida" << endl;
				}else{
					cout << " " << p->getNome() << "  mover para: ";
					cin >> letra >> x;
					y = traduz(&x, letra);
					if(p->movimento_possivel(b,x,y)){
						if(p->efetua_movimento(b,x,y) == 1)
							b.escreve_arquivo(jogadas_arq, x, y, 1);
						else
							b.escreve_arquivo(jogadas_arq, x, y, -1);
						jog = 1;
					}else
						cout << "Movimento falhou!" << endl;
					b.printBoard();
				}
				if(b.getState()) break;
			    if(b.check_xeque(1)){
			        std::cout<<" Rei Branco Esta em Cheque" << std::endl;
			    	jogadas_arq << "+";
			   	}
			}
			if(b.getState()) break;
		    contador++;
		    jogadas_arq << endl;
	    }
	    if(b.getRei(1)==NULL){
	    	jogadas_arq << "#" << endl << "0-1";
	    	cout << "Jogador 2 venceu!!" << endl;
	    }
	    else{
	    	jogadas_arq << "#" << endl << "1-0";
	    	cout << "Jogador 1 venceu!!" << endl;
	    }
	    cout << "\nFim de Jogo" << endl;
		return 0;
	}else {
		cout << "\nOpção de jogo com arquivo de notação em xadrez!" << endl;
		cout << "Entre com o nome do arquivo e extensão: ";
		char nome[120];
		cin >> nome;
		//getline(cin,nome);
		ifstream entradas(nome,ios::in);
		cout << "\nRecriando jogo a partir do arquivo \"" << nome << "\"\n" << endl;

		if (!entradas) cout << "WTF" << endl;
		Board tab("start");
		tab.printBoard();
		cout << endl;
		string j1, j2, isola, tipo;
		int x, y, contador = 1, jog = 1;
		while(!entradas.eof()){
			jogadas_arq << contador << ". ";
			Peca *p;
			entradas >> isola;
			if(isola == "1-0" || isola == "0-1") break;
			entradas >> j1;
			if(j1 == "1-0" || j1 == "0-1") break;
			cout << "Jogador 1: " << j1 << endl;
			tipo = traduz(j1, &x, &y);
			//cout << tipo << " " << x << " " << y << endl;
			p = tab.encontra_possivel(tipo, x, y, 1);
			if(p != NULL){
				if(p->efetua_movimento(tab,x,y) == 1)
					tab.escreve_arquivo(jogadas_arq, x, y, 1);
				else
					tab.escreve_arquivo(jogadas_arq, x, y, -1);
			} else
				cout << "Movimento falhou!" << endl;
			
			if(tab.check_xeque(1)){
			    std::cout<<" Rei Branco Esta em Cheque" << std::endl;
			  	jogadas_arq << "+";
			}
			tab.printBoard();
			cout << endl;
			entradas >> j2;
			if(j2 == "1-0" || j2 == "0-1") break;
			jogadas_arq << " ";
			cout << "Jogador 2: " << j2 << endl;
			tipo = traduz(j2, &x, &y);
			//cout << tipo << " " << x << " " << y << endl;
			p = tab.encontra_possivel(tipo, x, y, 2);
			if(p != NULL){
				if(p->efetua_movimento(tab,x,y) == 1)
					tab.escreve_arquivo(jogadas_arq, x, y, 1);
				else
					tab.escreve_arquivo(jogadas_arq, x, y, -1);
			}else
				cout << "Movimento falhou!" << endl;
			
			if(tab.check_xeque(1)){
			    std::cout<<" Rei Branco Esta em Cheque" << std::endl;
			  	jogadas_arq << "+";
			}
			tab.printBoard();
			cout << endl;
			contador++;	
			jogadas_arq << endl;
		}
		if(tab.getRei(1)==NULL){
	    	jogadas_arq << "#" << endl << "0-1";
	    	cout << "Jogador 2 venceu para o arquivo \"" << nome << "\"" << endl;
	    }
	    else{
	    	jogadas_arq << "#" << endl << "1-0";
	    	cout << "Jogador 1 venceu para o arquivo \"" << nome << "\"" << endl;
	    }
		cout << "\n      Fim de arquivo" << endl;
		return 0;
	}
}