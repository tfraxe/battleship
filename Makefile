makefile all: main

main.o: main.c ships.h tabuleiro.h input.h pilha.h jogadas.h
	gcc -g -c main.c

ships.o: ships.c ships.h tabuleiro.h
	gcc -g -c ships.c

tabuleiro.o: tabuleiro.c tabuleiro.h input.h
	gcc -g -c tabuleiro.c

input.o: input.c input.h
	gcc -g -c input.c

jogadas.o: jogadas.c ships.h tabuleiro.h input.h jogadas.h pilha.h
	gcc -g -c jogadas.c
pilha.o: pilha.c pilha.h
	gcc -g -c pilha.c


main: main.o ships.o tabuleiro.o input.o jogadas.o pilha.o
	gcc main.o ships.o tabuleiro.o input.o jogadas.o pilha.o -o main

clear:
	rm -f main
	rm -f *.o
