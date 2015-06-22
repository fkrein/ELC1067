#include "memo.h"
#include "lista.h"
#include "vertice.h"

void vertice_insere_aresta(vertice_t* v1, vertice_t* v2){
	lista_t* cpy;
	lista_t* new = memo_aloca(sizeof(lista_t));
	new->prox = NULL;
	new->vert = v2;
	cpy = v1->adjacentes;
	if(cpy == NULL){
		v1->adjacentes = new;
	}else{
		while(cpy->prox != NULL){
			cpy = cpy->prox;
		}
		cpy->prox = new;
	}
	new = memo_aloca(sizeof(lista_t));
	new->prox = NULL;
	new->vert = v1;
	cpy = v2->adjacentes;
	if(cpy == NULL){
		v2->adjacentes = new;
	}else{
		while(cpy->prox != NULL){
			cpy = cpy->prox;
		}
		cpy->prox = new;
	}
}