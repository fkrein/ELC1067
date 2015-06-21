#include <stdio.h>
#include <string.h>
#include "memo.h"
#include "lista.h"

lista_t* lista_insere_vertice(lista_t* list, struct vertice* v){
	lista_t* new = memo_aloca(sizeof(lista_t));
	new->prox = NULL;
	new->vert = v;
	if(list == NULL){
		return new;
	}
	lista_t* cpy = list;
	while(cpy->prox != NULL){
		cpy = cpy->prox;
	}
	cpy->prox = new;
	return list;
}

vertice_t* lista_busca_vertice(lista_t* list, char* chave){
	lista_t* cpy = list;
	while(strcmp(chave, cpy->vert->chave)){
		cpy = cpy->prox;
	}
	return cpy->vert;
}

void lista_imprime(lista_t* list){
	lista_t* cpy = list;
	while(cpy != NULL){
		printf("%s ", cpy->vert->chave);
		cpy = cpy->prox;
	}
}

lista_t* lista_remove_vertice(lista_t* list){
	lista_t* cpy = list->prox;
	memo_libera(list->vert->chave);
	memo_libera(list->vert->nome);
	memo_libera(list->vert);
	memo_libera(list);
	return cpy;
}