/*
 * vetor.c
 * TAD que implementa um vetor dinamico.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014, 2015 João V. Lima, UFSM
 *               2005       Benhur Stein, UFSM
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vetor.h"
#include "carta.h"
#include "memo.h"

#define QTDD 100

struct vetor {
	/* TODO aqui */
	/* defina os campos da TAD vetor aqui */
    int aux;
	carta* baralho;   /* baralho - vetor de cartas */
	int n;		/* número de cartas */
};

vetor_t* vetor_cria(void){
	vetor_t *vet = (vetor_t*)memo_aloca(sizeof(vetor_t));
	vet->n = 0;
	vet->aux = 0;
	//inicio
	int i;
    vet->baralho = (carta*)memo_aloca(QTDD*sizeof(carta));
    for(i=0;i<QTDD;i++){
        vet->baralho[i]=NULL;
    }
	//fim
	return vet;
}

void vetor_destroi(vetor_t* vet){
	memo_libera(vet->baralho);
	memo_libera(vet);
}

int vetor_numelem(vetor_t *vet){
	//Concluido
	return vet->n;
}

void vetor_insere_carta(vetor_t *vet, int indice, carta c){
	//início
	int i = (vet->n);
	int j;
	if((vet->n+1)%QTDD==0 && vet->aux!=-1){
        vet->baralho = (carta*) memo_realoca(vet->baralho,((vet->n)+1+QTDD)*sizeof(carta));
        for(j=vet->n;j<vet->n+QTDD;j++){
            vet->baralho[j]=NULL;
        }
	}
    while(i>indice){
        vet->baralho[i] = vet->baralho[i-1];
        i--;
    }
    vet->baralho[indice] = c;
	//fim
	vet->n++;
}

carta vetor_remove_carta(vetor_t *vet, int indice){
    carta i = vet->baralho[indice];
    if(i==NULL){
        return NULL;
    }
    vet->aux=-1;
    while(vet->baralho[indice]!=NULL){
        vet->baralho[indice] = vet->baralho[indice+1];
        indice++;
    }
	vet->n--;
	return i;
}

carta vetor_acessa_carta(vetor_t *vet, int indice){
	return vet->baralho[indice];
}

bool vetor_valido(vetor_t *vet){
	return true;
}
