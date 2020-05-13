#ifndef PILHA_H
#define PILHA_H

#include"input.h"
typedef struct stack {
	struct stack* prox;
	Coord coordenadas;
} Pilha;
Pilha* inicializarPilha();
Pilha* criaNo(Coord coordenadas);
void empilhar(Pilha** topo, Pilha* novo_no);
void desempilhar(Pilha** topo);

#endif

