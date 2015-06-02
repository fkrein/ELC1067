/*
 * principal.c
 * Implementação de árvore de expressões aritméticas.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. F. Lima, UFSM
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
#include <unistd.h>
#include <string.h>

#include "memo.h"
#include "arv.h"
#include "pilha.h"

int main(void){

	double operando;
	op_t oprd;
	arv_t* elemento;
	arv_t* removido;
	pilha_t* pilha = pilha_cria();

	char c;
	int length, index = 0;
	char* str = (char*) memo_aloca(sizeof(char));
	str[0] = '\0';
	char* aux = (char*) memo_aloca(sizeof(char));
	aux[0] = '\0';

	//ler dinamicamente a equação
	while((c = getchar()) != '\n'){
		length = strlen(str);
		str = memo_realoca(str, length + 2);
		str[length] = c;
		str[length + 1] = '\0';
	}


	while(str[index] != '\0'){
		while(str[index] != ' ' && str[index] != '\0'){
			length = strlen(aux);
			aux = memo_realoca(aux, length + 2);
			aux[length] = str[index];
			aux[length + 1] = '\0';
			index++;
		}
		length = 0;
		if(aux[0] >= '0' && aux[0] <= '9'){
			operando = atof(aux);
			oprd.tipo = OPERANDO;
			oprd.u.operando = operando;
			elemento = arv_cria(oprd);
		}else{
			oprd.tipo = OPERADOR;
			oprd.u.operador = aux[0];
			elemento = arv_cria(oprd);
			removido = pilha_remove(pilha);
			arv_insere_direita(elemento, removido);
			removido = pilha_remove(pilha);
			arv_insere_esquerda(elemento, removido);
		}
		pilha_insere(pilha, oprd);

		aux = memo_realoca(aux, sizeof(char));
		aux[0] = '\0';

		index++;
	}

	removido = pilha_remove(pilha);

	arv_imprime_pre_ordem(removido);
	arv_imprime_em_ordem(removido);
	arv_imprime_pos_ordem(removido);

	// /* exemplo simples de árvore */
	// arv_t* raiz;
	// op_t soma, n1, n2;
	// pilha_t* pilha;

	// /* inicia expressão */
	// /* operador + */
	// soma.tipo = OPERADOR;
	// soma.u.operador = '+';
	// /* primeiro operando */
	// n1.tipo = OPERANDO;
	// n1.u.operando = 1.0;
	// /* segundo operando */
	// n2.tipo = OPERANDO;
	// n2.u.operando = 2.0;

	// /* cria uma árvore */
	// raiz = arv_cria( soma );
	// raiz = arv_insere_esquerda( raiz, n1 );
	// raiz = arv_insere_direita( raiz, n2 );

	// /* simples uso da pilha */
	// pilha = pilha_cria();
	// pilha_insere( pilha, raiz );
	// pilha_destroi( pilha );

	// /* destroi árvore */
	// arv_destroi( raiz );
	memo_relatorio();
	return 0;
}
