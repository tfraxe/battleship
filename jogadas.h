#ifndef JOGADAS_H
#define JOGADAS_H
#include "pilha.h"
#include "input.h"
#include "tabuleiro.h"
#include "ships.h"
typedef struct _info {
	char jogador;
	Coord ultimaJogada;
	char embarcacaoAtingida;
	short int atingiuEmbarcacao;
	short int destruiuEmbarcacao;
	short int pontuacao;


} Info;

Coord calculaCoordenadas(Pilha* topo, int* vetor);
short int acertouEmbarcacao(Coord coordenadas, Board* tabuleiro);
short int destruiuEmbarcacao (Coord coordenadas, Board* tabuleiro);
Info jogadaComputador(Pilha** topo, int** vetor, Board* tabuleiro, Info computador);
Info jogadaHumano(Board* tabuleiro, Info humano);
short int destroiSubmarino(Board* tabuleiro, int tam);

#endif
