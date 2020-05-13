#ifndef SHIPS_H
#define SHIPS_H

#define PORTAAVIAO 'p'
#define DESTROYER 'd'
#define FRAGATA 'f'
#define SUBMARINO 's'
#define JANGADA 'j'

//Definição das orientações
#define HORIZONTAL 0
#define VERTICAL 1


typedef struct ship {
	short int vida;
	char tipo;
	short int orientacao;
	short int destruido;
} Embarcacao;

Embarcacao* criaEmbarcacao(char tipo);

#endif

