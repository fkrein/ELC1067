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
	while(strcmp(chave, cpy->vert->chave) && cpy != NULL){
		cpy = cpy->prox;
	}
	return cpy == NULL?NULL:cpy->vert;
}

void lista_imprime(lista_t* list){
	lista_t* cpy = list;
	while(cpy != NULL){
		printf("%s ", cpy->vert->chave);
		cpy = cpy->prox;
	}
}

lista_t* lista_remove_vertice(lista_t* list){
	vertice_t* cpy = list->vert;
	lista_t* cpy2 = list->prox;
	while(cpy->adjacentes != NULL){
		cpy->adjacentes = vertice_remove_aresta(cpy->adjacentes);
	}
	memo_libera(cpy->chave);
	memo_libera(cpy->nome);
	memo_libera(cpy);
	memo_libera(list);
	return cpy2;
}