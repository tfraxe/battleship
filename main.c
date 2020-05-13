/*                                                                   EQUIPE

	THIAGO FRAXE CORREIA PESSOA - Matrícula 397796
	JOÃO ESAÚ DE OLIVEIRA RODRIGUÊS - Matrícula 377735

														CONTRIBUIÇÃO DE CADA PARTICIPANTE

	Thiago Fraxe - Criou, desenolveu e fez os testes das funções presentes nos arquivos input.c, jogadas.c e  tabuleiro.c

	João Esaú - Criou, desenolveu e fez os testes das funções presentes nos arquivos ships.c, pilhas.c e main.c




*/


#include <stdlib.h>
#include <stdio.h>
#include "ships.h"
#include "tabuleiro.h"
#include "input.h"
#include "pilha.h"
#include "jogadas.h"
#include <time.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{	

	initRandom(); // Inicia o seed do gerador de números aleatórios.
	short int placarComputador;
	short int  placarHumano;
	placarComputador = 0;
	placarHumano = 0;
	short int continuar = FALSO;
	do{
		system("clear");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("                                                         B A T A L H A          N A V A L                              \n");
		sleep(5);
		char escolha;
		Board* tabuleiroH = criaTabuleiro(12); //Cria o tabuleiro do Humano, que será acessado pelo computador
		Board* tabuleiroC = criaTabuleiro(12); // Cria o tabuleiro do Computador, que será acessado pelo humano
		atribuiEmbarcacoes(tabuleiroH); // Coloca, no tabuleiro do humano, as embarcações
		atribuiEmbarcacoes(tabuleiroC); // Coloca, no tabuleiro do computador, as embarcações;
		atribuiSimbolos(tabuleiroH); //Adiciona ao tabuleiro do humano os símbolos correspondentes a cada embarcação
		atribuiSimbolos(tabuleiroC); //Adiicona ao tabuleiro do computador os símbolos correspondentes a cada embarcação
		desenhaTabuleiro2(tabuleiroH, tabuleiroC, 12); // Desenha, na tela, ambos os tabuleiros lado-a-lado. 

		Info humano; // registro que carregará as informações do Humano
		humano.jogador = 'h';
		humano.pontuacao = 0;

		Info computador;  // registro que carregará as informações do Computador
		computador.jogador = 'c';
		computador.pontuacao = 0;

		

		Pilha* topo = NULL; //Inicializa pilha que será utilizada para cálculo das coordenadas do computador
		int* posicoes = NULL; // Inicializa vetor que será utilizado para cálculo das coordenadas co computador

		char turno = 'h'; //Variável que determinará de quem é a vez de jogar. O turno será decidido conforme as especifições do trabalho.

		computador.ultimaJogada.linha = -1;
		computador.ultimaJogada.coluna = -1;
		while(computador.pontuacao < 8 && humano.pontuacao < 8) {


			humano.destruiuEmbarcacao = FALSO;
			computador.destruiuEmbarcacao = FALSO;

			
			switch (turno) {
			case 'h':
			humano = jogadaHumano(tabuleiroC, humano);
			if(humano.atingiuEmbarcacao) {
				if(humano.embarcacaoAtingida == JANGADA) {
					if(destroiSubmarino(tabuleiroH, 12))
						computador.pontuacao++;
					turno = 'c';
				} else {
					turno = 'h';
				}
			} else {
				turno = 'c';
			}

			break;
			case 'c':
			computador = jogadaComputador(&topo, &posicoes, tabuleiroH, computador);
			if(computador.atingiuEmbarcacao) {
				if(computador.embarcacaoAtingida == JANGADA) {
					if(destroiSubmarino(tabuleiroC, 12))
						humano.pontuacao++;
					turno = 'h';
				} else {
					turno = 'c';
				}
			} else {
				turno = 'h';
			}
			break; 
			}


				desenhaTabuleiro2(tabuleiroH, tabuleiroC, 12);

				if(humano.destruiuEmbarcacao) {
					switch(humano.embarcacaoAtingida) {
					case PORTAAVIAO:
					sleep(2);
					printf("Humano destruiu porta-aviao!\n");
					humano.pontuacao = humano.pontuacao +1;
					
					break;
					case FRAGATA:
					sleep(2);
					printf("Humano destruiu fragata!\n");
					humano.pontuacao = humano.pontuacao +1;
					
					break;
					case DESTROYER:
					sleep(2);
					printf("Humano destruiu Destroyer!\n");
					humano.pontuacao = humano.pontuacao +1;
					
					break;
					case SUBMARINO:
					sleep(2);
					printf("Humano destruiu submarino!\n");
					humano.pontuacao = humano.pontuacao +1;
					
					break;
					case JANGADA:
					sleep(2);
					printf("Humano destruiu jangada!\n");
					
					break;
					}

			}
			

			

		

				if(computador.destruiuEmbarcacao) {
					switch(computador.embarcacaoAtingida) {
					case PORTAAVIAO:
					//system("clear");
					printf("Computador destruiu porta-aviao!\n");
					computador.pontuacao++;
					//sleep(5);
					break;
					case FRAGATA:
					//system("clear");
					printf("Computador destruiu fragata!\n");
					computador.pontuacao++;
					//sleep(5);
					break;
					case DESTROYER:
					//system("clear");
					printf("Computador destruiu Destroyer!\n");
					computador.pontuacao++;
					//sleep(5);
					break;
					case SUBMARINO:
					//system("clear");
					printf("Computador destruiu submarino!\n");
					computador.pontuacao++;
					//sleep(5);
					break;
					case JANGADA:
					//system("clear");
					printf("Computador destruiu jangada!\n");
					//sleep(5);
					break;
					}

				}
			



			

			char colunaHumano, colunaComputador;
			int linhaHumano, linhaComputador;
			colunaHumano = (char) humano.ultimaJogada.coluna + 65;
			linhaHumano = humano.ultimaJogada.linha;
			//desenhaTabuleiro2(tabuleiroH, tabuleiroC, 12);
			printf("Ultima jogada do Humano: %c%d \n", colunaHumano, linhaHumano+1);
			if(computador.ultimaJogada.linha != -1){
				linhaComputador = computador.ultimaJogada.linha;
				colunaComputador = (char) computador.ultimaJogada.coluna + 65;
				printf("\nUltima jogada do Computador: %c%d\n", colunaComputador, linhaComputador+1);
			}

			printf("\nPontuacao do computador: %d\n", computador.pontuacao);
			printf("\nPontuacao do humano: %d\n", humano.pontuacao);
			
			

		}

		if(humano.pontuacao == 8) {
			system("clear");
			printf("O humano venceu!");
			placarHumano++;
			sleep(2);
		} else if (computador.pontuacao == 8) {
			system("clear");
			printf("O computador venceu!");
			placarComputador++;
			sleep(2);
		}

		system("clear");

		printf("+-------------------------------------------------------------------------------------+");
		printf("\n                                    PLACAR                                           ");
		printf("\n                           Computador: %d partidas ganhas                             ", placarComputador);
		printf("\n                           Humano:     %d partidas ganhas                             ", placarHumano);
		printf("\n+-------------------------------------------------------------------------------------+");

		sleep(2);

		system("clear");

		printf("                              Deseja continuar jogando?   <S/N>                           ");
		scanf(" %c", &escolha);
		if (escolha == 's' || escolha == 'S')
			continuar = VERDADEIRO;
		else
			continuar = FALSO;

		system("clear");



	} while(continuar);
	 
	

	
	return 0;
}