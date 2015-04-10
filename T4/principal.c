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
 *///

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memo.h"
#include "jogo.h"
#include "pilha.h"
#include "carta.h"
#include "fila.h"
#include "tela.h"
#include "vetor.h"

#define TAM 52

void new_game(jogo solit);

int main(void){
	
	jogo solit = jogo_cria();
	new_game(solit);
	//pilha_insere_carta(jogo_monte(solit), carta_cria(AS, OUROS));
	//pilha_insere_carta(jogo_monte(solit), carta_cria(REI, PAUS));
	//pilha_insere_carta(jogo_monte(solit), carta_cria(DAMA, COPAS));
	//pilha_insere_carta(jogo_monte(solit), carta_cria(2, PAUS));
	//pilha_insere_carta(jogo_monte(solit), carta_cria(10, ESPADAS));

	jogo_desenha(solit);
	while (!pilha_vazia(jogo_monte(solit))) {
		carta		c;
		tela_le(jogo_tela(solit));

		c = pilha_remove_carta(jogo_monte(solit));
		carta_abre(c);
		pilha_insere_carta(jogo_descartes(solit), c);

		jogo_desenha(solit);
	}
	tela_le(jogo_tela(solit));
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
}


