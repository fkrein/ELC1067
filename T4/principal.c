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
void submenu(jogo solit, int origem);
void xx(jogo solit, int origem, int destino);
void xa(jogo solit, int origem, int destino);
void ax(jogo solit, int origem, int destino);

int main(void){
	
	jogo solit = jogo_cria();
	char c;

	printw(" *******  *******           *******  *******  *******  ******* \n");
	printw(" *     *  *     *           *     *  *     *  *     *  *     * \n");
	printw(" *  Q  *  *  W  *           *  R  *  *  T  *  *  Y  *  *  U  * \n");
	printw(" *     *  *     *           *     *  *     *  *     *  *     * \n");
	printw(" *******  *******           *******  *******  *******  ******* \n");
	printw("                                                               \n");
	printw(" *******  *******  *******  *******  *******  *******  ******* \n");
	printw(" *     *  *     *  *     *  *     *  *     *  *     *  *     * \n");
	printw(" *  1  *  *  2  *  *  3  *  *  4  *  *  5  *  *  6  *  *  7  * \n");
	printw(" *     *  *     *  *     *  *     *  *     *  *     *  *     * \n");
	printw(" *******  *******  *******  *******  *******  *******  ******* \n");
	printw("\nGame: Solitaire\nDevelopers: João V. Lima, Benhur Stein, Franciel Krein");
	printw("\n\nPress any key to start!");
	
	c = tela_le(jogo_tela(solit));

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
	int valor;
	do{
		origem = tela_le(jogo_tela(solit));
		printw("\n%c",origem);
		valor = origem-49;
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
			case '1': case '2': case '3': case '4': case '5': case '6': case '7':
				submenu(solit,valor);
				break;
			case 'r': case 'R':
				if(pilha_vazia(solit->ases[0])){
					tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
					break;
				}
				destino = tela_le(jogo_tela(solit));
				printw(" %c",destino);
				ax(solit,0,destino-49);
			case 't': case 'T':
				if(pilha_vazia(solit->ases[1])){
					tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
					break;
				}
				destino = tela_le(jogo_tela(solit));
				printw(" %c",destino);
				ax(solit,1,destino-49);
			case 'y': case 'Y':
				if(pilha_vazia(solit->ases[2])){
					tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
					break;
				}
				destino = tela_le(jogo_tela(solit));
				printw(" %c",destino);
				ax(solit,2,destino-49);
			case 'u': case 'U':
				if(pilha_vazia(solit->ases[3])){
					tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
					break;
				}
				destino = tela_le(jogo_tela(solit));
				printw(" %c",destino);
				ax(solit,3,destino-49);
			default:
				tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
				break;
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

void submenu(jogo solit, int indice){
	char destino;
	if(pilha_vazia(solit->pilhas[indice])){
		tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		return;
	}
	destino = tela_le(jogo_tela(solit));
	printw(" %c",destino);
	if(indice == destino-49){
		tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		return;
	}
	switch(destino){
		case '1': case '2': case '3': case '4': case '5': case '6': case '7':
			xx(solit,indice,destino-49);
			break;
		case 'r': case 'R':
			xa(solit,indice,0);
			break;
		case 't': case 'T':
			xa(solit,indice,1);
			break;
		case 'y': case 'Y':
			xa(solit,indice,2);
			break;
		case 'u': case 'U':
			xa(solit,indice,3);
			break;
		default:
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
			break;
	}
}

void xx(jogo solit, int origem, int destino){
	carta c, cd;
	pilha aux = pilha_cria();
	int soma;
	if(pilha_vazia(solit->pilhas[destino])){
		c = pilha_remove_carta(solit->pilhas[origem]);
		while(carta_valor(c)!=13 && carta_aberta(c) && !pilha_vazia(solit->pilhas[origem])){
			pilha_insere_carta(aux,c);
			c = pilha_remove_carta(solit->pilhas[origem]);
		}
		if(carta_aberta(c)){
			pilha_insere_carta(aux,c);
		}else{
			pilha_insere_carta(solit->pilhas[origem],c);
		}
		c = pilha_remove_carta(aux);
		if(carta_valor(c) == 13){
			while(!pilha_vazia(aux)){
				pilha_insere_carta(solit->pilhas[destino],c);
				c = pilha_remove_carta(aux);
			}
			pilha_insere_carta(solit->pilhas[destino],c);
			if(!pilha_vazia(solit->pilhas[origem])){
				c = pilha_remove_carta(solit->pilhas[origem]);
				carta_abre(c);
				pilha_insere_carta(solit->pilhas[origem],c);
			}
			jogo_desenha(solit);
		}else{
			while(!pilha_vazia(aux)){
				pilha_insere_carta(solit->pilhas[origem],c);
				c = pilha_remove_carta(aux);
			}
			pilha_insere_carta(solit->pilhas[origem],c);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}else{
		c = pilha_remove_carta(solit->pilhas[origem]);
		cd = pilha_remove_carta(solit->pilhas[destino]);
		while(carta_valor(c)!=carta_valor(cd)-1 && carta_aberta(c) && !pilha_vazia(solit->pilhas[origem])){
			pilha_insere_carta(aux,c);
			c = pilha_remove_carta(solit->pilhas[origem]);
		}
		if(carta_aberta(c)){
			pilha_insere_carta(aux,c);
		}else{
			pilha_insere_carta(solit->pilhas[origem],c);
		}
		c = pilha_remove_carta(aux);
		soma = carta_naipe(c) + carta_naipe(cd);
		if(carta_valor(c) == carta_valor(cd)-1 && carta_naipe(c) != carta_naipe(cd) && soma>=2 && soma<=4){
			pilha_insere_carta(solit->pilhas[destino],cd);
			while(!pilha_vazia(aux)){
				pilha_insere_carta(solit->pilhas[destino],c);
				c = pilha_remove_carta(aux);
			}
			pilha_insere_carta(solit->pilhas[destino],c);
			if(!pilha_vazia(solit->pilhas[origem])){
				c = pilha_remove_carta(solit->pilhas[origem]);
				carta_abre(c);
				pilha_insere_carta(solit->pilhas[origem],c);
			}
			jogo_desenha(solit);
		}else{
			while(!pilha_vazia(aux)){
				pilha_insere_carta(solit->pilhas[origem],c);
				c = pilha_remove_carta(aux);
			}
			pilha_insere_carta(solit->pilhas[origem],c);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}
	pilha_destroi(aux);
}

void xa(jogo solit, int origem, int destino){
	carta c, cd;
	c = pilha_remove_carta(solit->pilhas[origem]);
	if(pilha_vazia(solit->ases[destino])){
		if(carta_valor(c) == 1){
			pilha_insere_carta(solit->ases[destino],c);
			if(!pilha_vazia(solit->pilhas[origem])){
				c = pilha_remove_carta(solit->pilhas[origem]);
				carta_abre(c);
				pilha_insere_carta(solit->pilhas[origem],c);
			}
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->pilhas[origem],c);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}else{
		cd = pilha_remove_carta(solit->ases[destino]);
		if(carta_valor(c) == carta_valor(cd)+1 && carta_naipe(c) == carta_naipe(cd)){
			pilha_insere_carta(solit->ases[destino],cd);
			pilha_insere_carta(solit->ases[destino],c);
			if(!pilha_vazia(solit->pilhas[origem])){
				c = pilha_remove_carta(solit->pilhas[origem]);
				carta_abre(c);
				pilha_insere_carta(solit->pilhas[origem],c);
			}
			jogo_desenha(solit);
		}else{
			pilha_insere_carta(solit->pilhas[origem],c);
			pilha_insere_carta(solit->ases[destino],cd);
			tela_escreve_esquerdado(solit->tela," - Comando Invalido!",20);
		}
	}
}

void ax(jogo solit, int origem, int destino){

}