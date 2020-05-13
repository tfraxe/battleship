#ifndef TABULEIRO_H
#define TABULEIRO_H

#define AGUA_SIMB '~'
#define JANGADA_SIMB '&'
#define SUBMARINO_SIMB '@'
#define SUP_VERTICAL '^'
#define INF_VERTICAL 'v'
#define SUP_HORIZONTAL '<'
#define INF_HORIZONTAL '>'
#define CORPO '#'
#define ATING_EMBARC '*'
#define ATING_AGUA 'O'

#define VERDADEIRO 1
#define FALSO 0

#define QTD_PORTAAVIAO 1
#define QTD_DESTROYER 2
#define QTD_FRAGATA 3
#define QTD_SUBMARINO 2
#define QTD_JANGADA 1

#include "input.h"
#include "ships.h"

typedef struct board {
	struct board* esq;
	struct board* dir;
	struct board* cima;
	struct board* baixo;
	Embarcacao* embarcacao;
	short int atingido;
	short int parte;
	char simbolo;

} Board;


Board* criaTabuleiro(int tam);

Board* acessaTabuleiro(Board* tabuleiro, int linha, int coluna);

short int cabe(Board* tabuleiro, short int orientacao, Coord coordenadas, short int tamanho);

short int existeEmbarcacao(Board* tabuleiro, short int orientacao, Coord coordenadas, short int tamanho);

Coord escolheCoordenada(Board* tabuleiro, Embarcacao* ship);

void colocaEmbarcacao(Board* tabuleiro, Embarcacao* ship);

void atribuiEmbarcacoes(Board* tabuleiro);

void atribuiSimbolos(Board* tabuleiro);

void desenhaTabuleiro2(Board* tabuleiroH, Board* tabuleiroC, int tam);

void initRandom();



#endif

