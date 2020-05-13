/*
+------------------------------------------------------------------------------------------------------------------------------+
Implementação de uma PILHA usando LISTA SIMPLESMENTE ENCADEADA. 


+-------------------------------------------------------------------------------------------------------------------------------+
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* inicializarPilha() {
	Pilha* topo;
	topo = NULL;
	return topo;
}

Pilha* criaNo(Coord coordenadas) {
	Pilha* novo_no = (Pilha*)malloc(sizeof(Pilha));
	novo_no->prox = NULL;
	novo_no->coordenadas = coordenadas;

	return novo_no;

}

void empilhar(Pilha** topo, Pilha* novo_no) {
	novo_no->prox = *topo;
	*topo = novo_no;
}

void desempilhar(Pilha** topo) {
	Pilha* aux = *topo;
	if(aux == NULL)
		return;
	else
		*topo = aux->prox;
}