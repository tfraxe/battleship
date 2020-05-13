#include <stdio.h>
#include <stdlib.h>
#include "ships.h"
#include "tabuleiro.h"
/*
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função Cria Embarcação
Versão: 2.0
Data: 09/12/2017
Comentário: Função que cria as instâncias das embarcações.
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
Embarcacao* criaEmbarcacao(char tipo) {
	Embarcacao* nova_embarcacao = (Embarcacao*)malloc(sizeof(Embarcacao)); // Aloca espaço para a nova embarcação

	switch (tipo) {
		case PORTAAVIAO:
			nova_embarcacao->vida = 5;
			nova_embarcacao->tipo = PORTAAVIAO;
			nova_embarcacao->destruido = FALSO;
			break;
		case DESTROYER:
			nova_embarcacao->vida = 3;
			nova_embarcacao->tipo = DESTROYER;
			nova_embarcacao->destruido = FALSO;
			break;
		case FRAGATA:
			nova_embarcacao->vida = 2;
			nova_embarcacao->tipo = FRAGATA;
			nova_embarcacao->destruido = FALSO;
			break;
		case SUBMARINO:
			nova_embarcacao->vida = 1;
			nova_embarcacao->tipo = SUBMARINO;
			nova_embarcacao->destruido = FALSO;
			break;
		case JANGADA:
			nova_embarcacao->vida = 1;
			nova_embarcacao->tipo = JANGADA;
			nova_embarcacao->destruido = FALSO;
			break;
	}

	nova_embarcacao->orientacao = HORIZONTAL;

	return nova_embarcacao;



}
