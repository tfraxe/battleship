#include <stdio.h>
#include <stdlib.h>
#include "ships.h"
#include "tabuleiro.h"
#include "input.h"
#include <time.h>

void initRandom() {
	srand(time(NULL));
}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Nome: Função que cria tabuleiro assim como especificado pelo professor
Versão: 2.0
Data: 09/12/2017
Comentário: esta função cria um tabuleiro quadrado de tamanho tam x tam. O tabuleiro em questão é uma matriz quadrada que utiliza os nós de Board definidos anterior
mente no header tabuleiro.h.  
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Board* criaTabuleiro(int tam) {

	Board* cima;
	Board* linha; /* Cima vai apontar para o primeiro nó da linha de cima; linha, para o primeiro nó da linha em que os nós estão sendo inseridos. */ 
	Board* aux;

	cima = NULL;
	linha = NULL;

	Board* novo_no; /* Cria ponteiro que aponta para novo nó */ 


	for(int i = 0; i < tam; i++) {
		for(int j = 0; j < tam; j++) {

			novo_no = (Board*)malloc(sizeof(Board)); //Criação do novo nó do tabuleiro. 
			novo_no->dir = linha;
			novo_no->esq = NULL;
			novo_no->baixo = NULL;
			novo_no->cima = cima;
			novo_no->embarcacao = NULL;
			novo_no->simbolo = 'a';
			novo_no->atingido = FALSO;

	
			if(linha != NULL) 
				linha->esq = novo_no;
			if (cima != NULL)
				cima->baixo = novo_no; 
	
			linha = novo_no;

			aux = linha->dir;

			while (aux != NULL && cima != NULL) {  // "Corrige" os outros nós quando um outro é inserido. Isto é, liga-os com os nós de cima correspondentes. 
				
				aux->cima = (aux->cima)->dir;
				(aux->cima)->baixo = aux;
				aux = aux->dir;
			}

			

		}

		cima = linha;
		linha = NULL;
	}
	
	//free(linha);
	//free(aux);


	for(int i = 0; i < tam-1; i++)
		cima = cima->cima; // Fazemos o ponteiro cima apontar para o primeiro nó do tabuleiro.

	return cima; //Retormaos cima. Este ponteiro servirá para termos acesso ao tabuleiro.

}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função para acessar nós de um tabuleiro
Versão: 2.0
Data: 09/12/2017
Comentário: Dadas as coordenadas das linhas e das colunas, esta função retorna um ponteiro para o nó que está nessa posição do tabuleiro.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Board* acessaTabuleiro(Board* tabuleiro, int linha, int coluna) {

	Board* ponteiro = tabuleiro;

	for(int i = 0; i < linha; i++)
		ponteiro = ponteiro->baixo; //O ponteiro anda tantas posições para baixos até alcançar a linha desejada. A primeira linha é a linha 0, assim como na matriz convencional.

	for(int j = 0; j < coluna; j++) //O mesmo do anterior, mas agora o ponteiro anda para direito até alcançar a coluna desejada. A primeira coluna é coluna 0.
		ponteiro = ponteiro->dir;

	return ponteiro;

}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função cabe
Versão: 2.0
Data: 09/12/2017
Comentário: Quando a posição da embarcação for escolhida aleatoriamente, esta função será chamada para determinar se a embarcação cabe ou não naquela posição. 
Isto é, se ela não vai ultrapassar os limites do tabuleiro quando for colocada ali. 
Se couber, a função retorna VERDADEIRO. Caso contrário, a função retorna FALSO.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

short int cabe(Board* tabuleiro, short int orientacao, Coord coordenadas, short int tamanho) {
	
	if (orientacao == HORIZONTAL) {
		if(coordenadas.coluna + tamanho <= 12)
			return VERDADEIRO;
	} else {
		if(coordenadas.linha + tamanho <= 12)
			return VERDADEIRO;
	}

	return FALSO;


}
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função existe
Versão: 2.0
Data: 09/12/2017
Comentário: Quando a posição da embarcação for escolhida aleatoriamente, esta função será chamada para determinar se existe ou não uma embarcação na posição escolhida. 
Se existir, a função retorna VERDADEIRO. Caso contrário, a função retorna FALSO.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

short int existeEmbarcacao(Board* tabuleiro, short int orientacao, Coord coordenadas, short int tamanho) {
	
	short int linha = coordenadas.linha;
	short int coluna = coordenadas.coluna;
	Board* ponteiro;
	if(orientacao == HORIZONTAL) {
		for(int i = 0; i < tamanho; i++) {
			ponteiro = acessaTabuleiro(tabuleiro, linha, coluna);
			coluna++;
			if(ponteiro->embarcacao != NULL)
				return VERDADEIRO;

		}
			
			return FALSO;
	} else {
		for(int i = 0; i < tamanho; i++) {
			ponteiro = acessaTabuleiro(tabuleiro, linha, coluna);
			linha++;
			if(ponteiro->embarcacao != NULL) {
				
				return VERDADEIRO;
			}
		}	
			
			return FALSO;
	}

}
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função escolhe
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função determinará aleatoriamente a coordenada do tabuleiro em que será colocada a embarcação e verificará se ela é uma coordenada válida; isto é,
se a embarcação 'cabe' na posição escolhida e se não existe uma outra embarcação naquela posição. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Coord escolheCoordenada(Board* tabuleiro, Embarcacao* ship) {

	
	short int tamanho = ship->vida;
	short int orientacao = ship->orientacao;
	Coord coordenadas;

	do
	{
		coordenadas.linha = rand() % 12;
		coordenadas.coluna = rand() % 12;

	} while ( !cabe(tabuleiro, orientacao, coordenadas, tamanho)  || existeEmbarcacao(tabuleiro, orientacao, coordenadas, tamanho) ); //Reduza parâmetros colocando só ship



	return coordenadas;


}
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função coloca
Versão: 2.0
Data: 09/12/2017
Comentário: Uma vez escolhidas as coordenadas, esta função efetivamente coloca a embarcação no tabuleiro; isto é, ela faz o atributo .embarcacao do nó do tabuleiro
apontar para uma instância de embarcação.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void colocaEmbarcacao(Board* tabuleiro, Embarcacao* ship) { //Coloca uma embarcação no tabuleiro
	
	Board* ponteiro;
	Coord coordenadas;

	coordenadas = escolheCoordenada(tabuleiro, ship);

	ponteiro = acessaTabuleiro(tabuleiro, coordenadas.linha, coordenadas.coluna);

	short int orientacao = ship->orientacao;
	short int tamanho = ship->vida;

	if (orientacao == HORIZONTAL) {
		for(int i = 0; i < tamanho; i++){
			ponteiro->embarcacao = ship;
			ponteiro->parte = i; // Se parte = 0, então estamos colocando a parte superior da embarcação. Se 1 <= parte < embarcacao->vida - 1, então estamos colocando a parte do meio da embarcação. Se parte = embarcacao->vida - 1, estamos colocando a parte inferior.
			ponteiro = ponteiro->dir;
		}
	} else {
		for (int i = 0; i < tamanho; i++) {
			ponteiro->embarcacao = ship;
			ponteiro->parte = i;
			ponteiro = ponteiro->baixo;
		}
	}



}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função atribui
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função cria as instâncias de embarcações e as coloca no tabuleiro
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void atribuiEmbarcacoes(Board* tabuleiro) {


	
	// Criação de um Porta-Aviões
	Embarcacao* portaAviao = criaEmbarcacao(PORTAAVIAO);
	portaAviao->orientacao = rand() % 2;

	//Criação dos Destroyers
	Embarcacao* destroyer[QTD_DESTROYER];
	for(int i = 0 ; i < QTD_DESTROYER; i++) {
		destroyer[i] = criaEmbarcacao(DESTROYER);
		destroyer[i]->orientacao = rand() % 2;
	}

	//Criação das Fragatas
	Embarcacao* fragata[QTD_FRAGATA];
	for(int i = 0; i < QTD_FRAGATA; i++) {
		fragata[i] = criaEmbarcacao(FRAGATA);
		fragata[i]->orientacao = rand() % 2;
	}

	//Criação dos Submarinos
	Embarcacao* submarino[QTD_SUBMARINO];
	for(int i = 0; i < QTD_SUBMARINO; i++) {
		submarino[i] = criaEmbarcacao(SUBMARINO);
		submarino[i]->orientacao = rand() % 2;
	}

	//Criação de uma Jangada
	Embarcacao* jangada = criaEmbarcacao(JANGADA);
	jangada->orientacao = rand() % 2;



	//Coloca Porta-Avioes no tabuleiro;	
	colocaEmbarcacao(tabuleiro, portaAviao);

	// Coloca Destroyers no tabuleiro;
	for(int i = 0 ; i < QTD_DESTROYER; i++) {
		colocaEmbarcacao(tabuleiro, destroyer[i]);
	}

	// Coloca Fragatas no tabuleiro;
	for(int i = 0; i < QTD_FRAGATA; i++) {
		colocaEmbarcacao(tabuleiro, fragata[i]);
	}

	// Coloca Submarinos no tabuleiro;
	for(int i = 0; i < QTD_SUBMARINO; i++) {
		colocaEmbarcacao(tabuleiro, submarino[i]);
	}

	// Coloca Jangada no tabuleiro;
	colocaEmbarcacao(tabuleiro, jangada);


}
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função atribui
Versão: 2.0
Data: 09/12/2017
Comentário: Uma vez que as embarcações foram distruídas na embarcação, esta função coloca os símbolos no nós, de acordo com o tipo de embarcação presente  no nó.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void atribuiSimbolos(Board* tabuleiro) {
	Board* ponteiro;
	char tipoEmbarcacao;
	Embarcacao* embarcacao;
	for(int i = 0; i < 12; i++)
		for(int j = 0; j< 12; j++ ) {
			
			ponteiro = acessaTabuleiro(tabuleiro, i, j);
			embarcacao = ponteiro->embarcacao;
			if (embarcacao != NULL) {
				tipoEmbarcacao = embarcacao->tipo;
			}
			else {
				tipoEmbarcacao = 'a';
			}
			

			switch(tipoEmbarcacao) {

				case JANGADA:
				ponteiro->simbolo = JANGADA_SIMB;
				break;
				case SUBMARINO:
				ponteiro->simbolo = SUBMARINO_SIMB;
				break;
				case FRAGATA:
				if(embarcacao->orientacao == HORIZONTAL) {
					if(ponteiro->parte == 0) // Neste caso, parte = 0 implica parte SUPERIOR.
						ponteiro->simbolo = SUP_HORIZONTAL;
					else
						ponteiro->simbolo = INF_HORIZONTAL; // Parte = 1 implica parte INFERIOR.
				} else {
					if(ponteiro->parte == 0)
						ponteiro->simbolo = SUP_VERTICAL;
					else
						ponteiro->simbolo = INF_VERTICAL;
				}

				break;

				case DESTROYER:

				if(embarcacao->orientacao == HORIZONTAL) {
					if(ponteiro->parte == 0) // Parte = 0 implica parte SUPERIOR.
						ponteiro->simbolo = SUP_HORIZONTAL;
					else if(ponteiro->parte == 1) // Parte = 1 implica parte do MEIO (CORPO)
						ponteiro->simbolo = CORPO;
					else
						ponteiro->simbolo = INF_HORIZONTAL; // Parte = 2 implica parte INFERIOR.
				} else {
					if(ponteiro->parte == 0)
						ponteiro->simbolo = SUP_VERTICAL;
					else if(ponteiro->parte == 1)
						ponteiro->simbolo = CORPO;
					else
						ponteiro->simbolo = INF_VERTICAL;
				}


				break;

				case PORTAAVIAO:
				if(embarcacao->orientacao == HORIZONTAL) {
					if(ponteiro->parte == 0) // Parte = 0 implica parte SUPERIOR
						ponteiro->simbolo = SUP_HORIZONTAL;
					else if(ponteiro->parte >= 1 && ponteiro->parte <= 3) // Implica parte do MEIO (CORPO)
						ponteiro->simbolo = CORPO;
					else
						ponteiro->simbolo = INF_HORIZONTAL; // Parte = 4 implica parte INFERIOR
				} else {
					if(ponteiro->parte == 0)
						ponteiro->simbolo = SUP_VERTICAL;
					else if(ponteiro->parte >= 1 && ponteiro->parte <= 3)
						ponteiro->simbolo = CORPO;
					else
						ponteiro->simbolo = INF_VERTICAL;
				}



				break;

				default: // Se o nó não tiver embarcação, então o símbolo colocado será o de ÁGUA.
				ponteiro->simbolo = AGUA_SIMB;



			}
		}
}

/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função desenha
Versão: 2.0
Data: 09/12/2017
Comentário: Esta função desenha, na tela, os tabuleiros do computador e do humano, lado-a-lado. 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/


void desenhaTabuleiro2(Board* tabuleiroH, Board* tabuleiroC, int tam) {


 system("clear");
 Board* coluna;
 Board* linha;

 Board* coluna2;
 Board* linha2;

 coluna = tabuleiroH;
 linha = tabuleiroH;

 coluna2 = tabuleiroC;
 linha2 = tabuleiroC;

 Embarcacao* embarcacao;

	printf("          Humano                                    Computador\n\n");
	printf("   A B C D E F G H I J K L		     A B C D E F G H I J K L\n \n");

 for (int i = 0; i < tam; i++) {
 	if (i+1 < 10)
 		printf("0%d|", i+1);
 	else
 		printf("%d|", i+1);
 	for (int j = 0; j < tam; j++) {
 		if (coluna->embarcacao != NULL) {
 			if(coluna->atingido)
 				printf("%c|", ATING_EMBARC);
 			else
 				printf("%c|", coluna->simbolo);
 		} else {
 			if(coluna->atingido)
 				printf("%c|", ATING_AGUA);
 			else
 				printf("%c|", coluna->simbolo);
 		}
 		coluna = coluna->dir;
 	}

 	printf("               ");
 	if (i+1 < 10)
 		printf("0%d|", i+1);
 	else
 		printf("%d|", i+1);
 	
 	for (int k = 0; k < tam; k++) {
 		if(coluna2->embarcacao != NULL) {
 			embarcacao = coluna2->embarcacao;
 			if(embarcacao->vida == 0)
 				printf("%c|", coluna2->simbolo);
 			else if(coluna2->atingido)
 				printf("%c|", ATING_EMBARC);
 			else
 				printf(" |");

 		} else {
 			if(coluna2->atingido == VERDADEIRO)
 				printf("%c|", ATING_AGUA);
 			else
 				printf(" |");
 		}
 
 		coluna2 = coluna2->dir;
 	}


 	printf("\n");
 	linha = linha->baixo;
 	coluna = linha;

 	linha2 = linha2->baixo;
 	coluna2 = linha2;
 }


 //free(coluna);
 //free(linha);

}

