# xadrez-cpp
Xadrez usando polimorfismo em C++ com classes

Este programa é composto para 2 tipos de funcionamento:
<1> Jogo entre dois jogadores físicos, onde cada jogador escolhe uma peça do tabuleiro
pela ordem específica LETRA NUMERO e depois escolhe onde esta peça deve ir pela mesma regra.
Seguindo as regras do xadrez até quando um dos jogadores capturar o rei inimigo.

<2> Recriando um jogo a partir da leitra de um arquivo com notação algébrica de xadrez
Aqui neste ponto vale ressaalvtar que neste programa não está implementado as funções de 
Roque maior, roque menor e en passant. Nesse caso, se seu arquivo contém jogadas assim, o programa
retornará erro na jogada mesmo que ela esteja válida.

Para os testes de arquivo está disponível o arquivo teste.txt com um jogo pronto com xeque e xeque-mate.
O arquivo jogadas.txt é criado escrevendo as jogadas da partida.
