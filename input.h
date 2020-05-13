#ifndef INPUT_H
#define INPUT_H
typedef struct coord {
	int linha;
	int coluna;
} Coord;

int transformaLetra(char coluna);

Coord pegarCoordenada(char* s);
#endif
