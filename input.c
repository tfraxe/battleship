#include <stdio.h>
#include <stdlib.h>
#include "input.h"

/* 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função transformaLetra
Data: 29/11/2017
Versão: 2.0
Comentário: Dada um caractere, esta função retorna um número inteiro tal que possa ser utilizado para o acesso dos nós do nosso tabuleiro. Se o caractere não estiver entre
os válidos, a função retorna o valor -1, que servirá para indicar uma entrada inválida. 

+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


*/

int transformaLetra(char coluna) {
	int asc = (int) coluna; //Este cast retorna o código ASC do caractere guardado em coluna. 

	if( (asc >= 65) && (asc <= 76)  )
		return asc-65;
	else if ( (asc >= 97) && (asc <= 108) )
		return asc-97;
	return -1;
}

/* 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Função para pegar coordenadas da string entrada pelo usuário
Data: 29/11/2017
Versão: 2.0
Comentário: Função deve receber como parâmetro uma string. Ele deve retornar struct com as coordenadas. 
Esta função pega, da string, apenas os caracteres que importam, a letra e o número, e os transforma em números, que serão utilizadas para acessar a coluna e a linha do tabuleiro, respectivamente.
Porém, se mais de uma letra for encontrada, ou se forem encontrados dígitos separados por outros caracteres, a função retorna o valor -1, que servirá para indicar um vallor
inválido.  

+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


*/

Coord pegarCoordenada(char* s) {

	int i = 0;
	int linha = -1; //Se ao final do while linha continuar igual a -1, isto significa que nenhum número foi encontrado.
	char coluna = 'z'; // Se ao final do while coluna continuar igual a z, isto significa que nenhuma letra foi encontrada.
	int asc;
	int invalido = 0;
	int posPrimeiraLetra = 0; //Guarda a posição na string da primeira letra encontrada. 

	while (s[i] != '\0' && !invalido) {
		asc = (int) s[i];
		if( ( (asc >= 65) && (asc <= 76) ) || ( (asc >= 97) && (asc<=108) ) ) // Se for uma LETRA
			if(coluna != 'z'){ //Se coluna é diferente de z, então um caractere já foi encontrado anteriormente na string. Portanto, a entrada é inválida. 
				coluna = 'z';
				invalido = 1;
			} else {
				coluna = s[i];
		}
		else if( (asc >= 48) && ( asc <= 57) ) { // Se for um número
			
			if(linha != -1) { // Se linha é diferente de -1, isto significa que um número já foi encontrado na string. 
				if( (i - posPrimeiraLetra) > 1) { // Se a posição atual menos a posição da primeitra letra encontrada for maior do que 1, isto signifca que os números estão separados por algum caractere
					linha = -1;
					invalido = 1;
				}else {
					linha = (linha+1)*10;
					linha = linha + (asc - 49);
				}
			} else {
	
				linha = asc - 49;
				posPrimeiraLetra = i;
			}


		}

		i++;


	}



	Coord coordenadas;
	coordenadas.coluna = transformaLetra(coluna); // Função definida acima
	coordenadas.linha = linha;

	return coordenadas;



}
