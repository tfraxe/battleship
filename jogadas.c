#include <stdio.h>
#include <stdlib.h>
#include "ships.h"
#include "tabuleiro.h"
#include "input.h"
#include "jogadas.h"
#include "pilha.h"
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função calcula
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função irá calcular as coordenadas de 'ataque' do computador. Se o computador não tiver acertado ninguém ou se ele tiver acabado de destruir uma 
embarcação, topo será NULL e o cálculo das coordenadas será completamente aleatório.
Se, porém, o contrário acontecer, o cálculo das coordenadas será feito com base na coordenada presente no TOPO da pilha e no vetor.
O vetor servirá para indicar se o computador se moverá para frente, para baixo ou para os lados. A coordenada no topo da pilha servirá para indicar a origem
do movimento. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Coord calculaCoordenadas(Pilha* topo, int* vetor) {

	Coord coordenadas;
	int posicao;
	if (topo == NULL) {
		coordenadas.linha = rand() % 12;
		coordenadas.coluna = rand() % 12;
		return coordenadas;
	} else {
		posicao = *vetor;
		coordenadas = topo->coordenadas;

		switch (posicao) {
			case 0:
			coordenadas.linha++;
			break;
			case 1:
			coordenadas.coluna--;
			break;
			case 2:
			coordenadas.linha--;
			break;
			case 3:
			coordenadas.coluna++;
			break;
		}

		return coordenadas;
	}
}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função acertou
Versão: 2.0
Data: 09/12/2017
Comentário: Dada uma coordenada e um tabuleiro, esta função verificará se uma embarcação foi atingida. Em caso positivo, a função decrementa a VIDA da embarcação e 
retorna VERDADEIRO. Caso contrário, retorna FALSO.
Consideramos que uma embarcação já atingida equivale a não acertar uma embarcação.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

short int acertouEmbarcacao(Coord coordenadas, Board* tabuleiro) {
	Board* ponteiro;
	ponteiro = acessaTabuleiro(tabuleiro, coordenadas.linha, coordenadas.coluna);
	Embarcacao* ship = ponteiro->embarcacao;
	short int vida;

	if (ship == NULL) {
		ponteiro->atingido = VERDADEIRO;
		ponteiro->simbolo = ATING_AGUA;
		return FALSO;
	}
	else {
		if(ponteiro->atingido == VERDADEIRO)
			return FALSO;
		else {

			ponteiro->atingido = VERDADEIRO;

			if(ship->vida > 0)
				ship->vida = ship->vida - 1;
			return VERDADEIRO;
		}
	}

}
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função destruiu
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função verificará se a embarcação foi ou não destruída.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

short int destruiuEmbarcacao (Coord coordenadas, Board* tabuleiro) {
	Board* ponteiro;
	ponteiro = acessaTabuleiro(tabuleiro, coordenadas.linha, coordenadas.coluna);
	Embarcacao* ship = ponteiro->embarcacao;

	if (ship == NULL)
		return FALSO;
	else {
		if(ship->vida == 0  && ship->destruido == FALSO)
			return VERDADEIRO;
		return FALSO;
	}
}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função Jogada do Computador
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função controlará as jogadas do computador. As coordenadas, como vimos, serão ou escolhidas aleatoriamente, ou escolhidas com base na última posição
atingida pelo computador. 

Usamos uma PILHA para acompanhar as últimas posições atingidas. O vetor será utilizada para determinar se o computador se move para cima, para baixo ou para os lados.

O cálculo da coordenada será não-aleatório até que o computador destrua alguma embarcação. Se o computador, ao acessar as casas adjacentes ao nó atingido, encontrar 
ÁGUA, a pilha é desimpilhada e o vetor desloca para direita. Isto fará com que o computador procure em outras direções, até destruir uma embarcação. 

Retorna um struct com as informações da última jogada, se acertou ou não embarcação, se destruiu ou não embarcação, e, se tiver atingido uma embarcação
o tipo de embarcação que foi atingida. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Info jogadaComputador(Pilha** topo, int** vetor, Board* tabuleiro, Info computador) {
	Coord coordenadas = calculaCoordenadas(*topo, *vetor);
	Pilha* ponteiro = *topo;
	int contador = 0; 
	short int acertou = FALSO;
	short int destruiu = FALSO;
	Board* board;
	Embarcacao* embarcacao;

	while(coordenadas.linha < 0 || coordenadas.coluna < 0 || coordenadas.linha > 11 || coordenadas.coluna > 11) { //Se a coordenada escolhida não for válida, a função calculaCoordenadas é novamente chamada, até que uma coordenada válida seja escolhida.

		if (*topo != NULL) {
			while(ponteiro->prox != NULL) {
				ponteiro = ponteiro->prox;
				contador++;
			}


			for(int i = 0; i < contador; i++) 
				desempilhar(topo);
		}

		if( *vetor != NULL)
			*vetor = *vetor + 1;

		coordenadas = calculaCoordenadas(*topo, *vetor);
		computador.atingiuEmbarcacao = FALSO;
		computador.ultimaJogada = coordenadas; //Lmebrando que -1 é o padrão para jogada inválida. 
	} 


		   acertou = acertouEmbarcacao(coordenadas, tabuleiro);
		   destruiu = destruiuEmbarcacao(coordenadas, tabuleiro); 
		   board = acessaTabuleiro(tabuleiro, coordenadas.linha, coordenadas.coluna);
		   embarcacao = board->embarcacao;
		   
		   computador.ultimaJogada = coordenadas;
		   computador.atingiuEmbarcacao = acertou;
		   computador.destruiuEmbarcacao = destruiu;

		   if(destruiu) { //Se uma embarcação for destruída, a pilha é totalmente desempilha e o vetor é setado para NULL. 
		  		if(*topo != NULL)
		   			*topo = NULL; //Alternativa: free(*topo);
		   		if (*vetor != NULL)
		   			*vetor = NULL; //Alternativa: free(*vetor);
		   		computador.embarcacaoAtingida = embarcacao->tipo;
		   		embarcacao->destruido = VERDADEIRO;
		   } else {

			   	if(acertou) { // Se uma embarcação foi atingida mas não destruída, a coordenada do nó atingido é empilhada. 
			   		Pilha* novo_no = criaNo(coordenadas);
			   		empilhar(topo, novo_no);

			   		if(*vetor == NULL) { //Se o vetor era NULL, aloca-se espaço para ele. 
			   			*vetor = (int*)malloc(4*sizeof(int));
			   			for (int i = 0; i < 4; i++)
			   				*(*vetor + i) = i;
			   		}

			   		computador.embarcacaoAtingida = embarcacao->tipo;
			   		embarcacao->destruido = FALSO;

			   	} else {
				   		if (*topo != NULL) { //Se nada foi atingido e a pilha não era vazia, isto significa que o cálculo estava sendo feito de modo não aleatório. A pilha é desempilhada até a primeira coordenada inserida, para que o computador acesse outras casas adjacentes.
							while(ponteiro->prox != NULL) {
								ponteiro = ponteiro->prox;
								contador++;
							}


							for(int i = 0; i < contador; i++) 
								desempilhar(topo);
						}

							if( *vetor != NULL)
								*vetor = *vetor + 1;



				   	}


			}

	

	return computador;
}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função Jogada do Humano
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função recebe e trata as coordenadas entradas pelo humano e verifica se, na posição escolhida, uma embarcação foi ou não atingida, e se ela foi 
ou não destruída. Retorna um STRUCT com as informações da última jogada, se acertou ou não embarcação, se destruiu ou não embarcação, e, se tiver atingido uma embarcação
o tipo de embarcação que foi atingida. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Info jogadaHumano(Board* tabuleiro, Info humano) {
	short int invalido = FALSO;
	char* s = (char*)malloc(20*sizeof(char));
	printf("\nDigite as coordenadas: ");
	fgets(s, 20, stdin);
	Coord coordenadas;
	coordenadas = pegarCoordenada(s);
	Board* board;

	do {
		if(coordenadas.linha == -1 || coordenadas.coluna == -1 || coordenadas.linha > 11 || coordenadas.coluna > 11) {
			invalido = VERDADEIRO;
			printf("\n Coordenadas invalidas! Digite novamente: ");
			fgets(s, 20, stdin);
			coordenadas = pegarCoordenada(s);
		}
		else
			invalido = FALSO;
		

	} while(invalido);

	humano.atingiuEmbarcacao = acertouEmbarcacao(coordenadas, tabuleiro);
	humano.destruiuEmbarcacao = destruiuEmbarcacao(coordenadas, tabuleiro);
	humano.ultimaJogada = coordenadas;
	
	board = acessaTabuleiro(tabuleiro, coordenadas.linha, coordenadas.coluna);
	Embarcacao* ship;
	ship = board->embarcacao;

	if(humano.destruiuEmbarcacao)
		ship->destruido = VERDADEIRO;

	if(ship != NULL)
		humano.embarcacaoAtingida = ship->tipo;

	return humano;



}


/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função Destrói Submarino
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função destruirá um submarino do jogador caso este atinja uma JANGADA inimiga. Retorna VERDADEIRO caso um submarino não-destruído tenha sido encontrado.
Este retorno é importante para a composição das pontuações dos jogadores. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

short int destroiSubmarino(Board* tabuleiro, int tam) {

	 Board* coluna;
	 Board* linha;

	 coluna = tabuleiro;
	 linha = tabuleiro;



	 for (int i = 0; i < tam; i++) {

	 	for (int j = 0; j < tam; j++) {
	 		if(coluna->embarcacao != NULL)
	 			if( (coluna->embarcacao)->tipo == JANGADA && (coluna->embarcacao)->vida > 0) {
	 				(coluna->embarcacao)->vida = 0;
	 				(coluna->embarcacao)->destruido = VERDADEIRO;
	 				coluna->atingido = VERDADEIRO;
	 				return VERDADEIRO;
	 			}
	 		coluna = coluna->dir;
	 	}


	 	linha = linha->baixo;
	 	coluna = linha;

	 }

	return FALSO;
}
