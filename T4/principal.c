/*
 * principal.c Esse programa testa as TADs implementadas para um jogo
 * solitário.
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. Lima, UFSM 2005       Benhur Stein, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <ctype.h>

#include "memo.h"
#include "jogo.h"
#include "pilha.h"
#include "carta.h"
#include "fila.h"
#include "tela.h"
#include "vetor.h"

#define TAM 52

void new_game(jogo solit);
void menu(jogo solit);
void wq(jogo solit);
void qw(jogo solit);
void wx(jogo solit, int indice);
void wa(jogo solit, int indice);

int main(void){
	
	jogo solit = jogo_cria();

	new_game(solit);
	menu(solit);

	jogo_destroi(solit);
	memo_relatorio();
	return 0;
}

void new_game(jogo solit){
	vetor_t* cartas_ord = vetor_cria();
	vetor_t* cartas = vetor_cria();
	int i, j;
	carta c;
	srand(time(NULL));
	for(i=0; i<4; i++){
		for(j=1; j<=13; j++){
			vetor_insere_carta(cartas_ord,0,carta_cria(j,i));
		}
	}
	for(i=0; i<TAM; i++){
		c = vetor_remove_carta(cartas_ord,rand()%vetor_numelem(cartas_ord));
		vetor_insere_carta(cartas,0,c);
	}
	vetor_destroi(cartas_ord);
	for(i=0; i<7; i++){
		for(j=0; j<=i; j++){
			c = vetor_remove_carta(cartas,0);
			pilha_insere_carta(jogo_pilha(solit,i), c);
		}
		carta_abre(c);
	}
	for(i=0; i<24;i++){
		c = vetor_remove_carta(cartas,0);
		pilha_insere_carta(jogo_monte(solit), c);
	}
	vetor_destroi(cartas);
	jogo_desenha(solit);
}

void menu(jogo solit){
	char origem, destino;
	int qtdd;
	do{
		origem = tela_le(jogo_tela(solit));
		printw("\n%c",origem);
		switch(origem){
			case 'q': case 'Q':
				if(pilha_vazia(solit->monte)){
					wq(solit);
				}else{
					qw(solit);
				}
				break;
			case 'w': case 'W':
				if(pilha_vazia(solit->descartes)){
					tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
					break;
				}
				destino = tela_le(jogo_tela(solit));
				printw(" %c",destino);
				switch(destino){
					case '1': case '2': case '3': case '4': case '5': case '6': case '7':
						wx(solit,atoi(&destino)-1);
						break;
					case 'r': case 'R':
						wa(solit,0);
						break;
					case 't': case 'T':
						wa(solit,1);
						break;
					case 'y': case 'Y':
						wa(solit,2);
						break;
					case 'u': case 'U':
						wa(solit,3);
						break;
					default:
						tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
						break;
				}
				break;
			default:
				tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
		
	}while(origem != 27);
}

void wq(jogo solit){
	carta c;
	while(!pilha_vazia(solit->descartes)){
		c = pilha_remove_carta(solit->descartes);
		carta_fecha(c);
		pilha_insere_carta(solit->monte,c);
	}
	jogo_desenha(solit);
}

void qw(jogo solit){
	carta c;
	c = pilha_remove_carta(solit->monte);
	carta_abre(c);
	pilha_insere_carta(solit->descartes,c);
	jogo_desenha(solit);
}

void wx(jogo solit, int indice){
	carta c, cd;
	int soma;
	c = pilha_remove_carta(solit->descartes);
	if(pilha_vazia(solit->pilhas[indice])){
		if(carta_valor(c) == 13){
			pilha_insere_carta(solit->pilhas[indice],c);
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->descartes,c);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}else{
		cd = pilha_remove_carta(solit->pilhas[indice]);
		soma = carta_naipe(c) + carta_naipe(cd);
		if(carta_valor(c) == carta_valor(cd)-1 && carta_naipe(c) != carta_naipe(cd) && soma>=2 && soma<=4){
			pilha_insere_carta(solit->pilhas[indice],cd);
			pilha_insere_carta(solit->pilhas[indice],c);
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->descartes,c);
			pilha_insere_carta(solit->pilhas[indice],cd);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}
}

void wa(jogo solit, int indice){
	carta c, cd;
	c = pilha_remove_carta(solit->descartes);
	if(pilha_vazia(solit->ases[indice])){
		if(carta_valor(c) == 1){
			pilha_insere_carta(solit->ases[indice],c);
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->descartes,c);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}else{
		cd = pilha_remove_carta(solit->ases[indice]);
		if(carta_valor(c) == carta_valor(cd)+1 && carta_naipe(c) == carta_naipe(cd)){
			pilha_insere_carta(solit->ases[indice],cd);
			pilha_insere_carta(solit->ases[indice],c);
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->descartes,c);
			pilha_insere_carta(solit->ases[indice],cd);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}
}