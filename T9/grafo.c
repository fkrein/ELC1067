#include <stdio.h>
#include "grafo.h"

grafo_t* grafo_cria(void){
	grafo_t* grafo = memo_aloca(sizeof(grafo_t));
	grafo->nvertices = 0;
	grafo->vertices = NULL;
	return grafo;
}

bool grafo_insere_vertice(grafo_t* g, vertice_t* v){
	g->nvertices++;
	g->vertices = lista_insere_vertice(g->vertices, v);
	return true;
}

vertice_t* grafo_busca_vertice(grafo_t* g, char* chave){
	return lista_busca_vertice(g->vertices, chave);
}

bool grafo_insere_aresta(grafo_t* g, char* v1, char* v2){
	vertice_insere_aresta(grafo_busca_vertice(g, v1), grafo_busca_vertice(g, v2));
	return true;
}

void grafo_imprime(grafo_t* g){
	lista_t* cpy = g->vertices;
	while(cpy != NULL){
		printf("%s -> ", cpy->vert->chave);
		lista_imprime(cpy->vert->adjacentes);
		printf("\n");
		cpy = cpy->prox;
	}
}

void grafo_destroi(grafo_t* g){
	lista_t* cpy = g->vertices;
	while(cpy != NULL){
		cpy = lista_remove_vertice(cpy);
	}
	memo_libera(g);
}