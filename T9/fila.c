#include <stdbool.h>
#include "fila.h"
#include "memo.h"

fila_t* fila_cria(void){
	fila_t* Q = (fila_t*) memo_aloca(sizeof(fila_t));
	Q->first = NULL;
	Q->last = NULL;
	return Q;
}

fila_t* fila_insere(fila_t* Q, vertice_t* s){
	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->vert = s;
	novo->prox = NULL;
	if(Q->last == NULL){
		Q->first = novo;
	}else{
		Q->last->prox = novo;
	}
	Q->last = novo;
	return Q;
}

bool fila_vazia(fila_t* Q){
	return Q->first == NULL;
}

vertice_t* fila_remove(fila_t* Q){
	lista_t* cpy = Q->first;
	vertice_t* cpy2 = cpy->vert;
	Q->first = Q->first->prox;
	if(Q->first == NULL){
		Q->last = NULL;
	}
	memo_libera(cpy);
	return cpy2;
}

void fila_destroi(fila_t* Q){
	memo_libera(Q);	
}