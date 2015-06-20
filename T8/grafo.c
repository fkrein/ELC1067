#include "grafo.h"

/* cria um grafo vazio */
grafo_t* grafo_cria(void){
	grafo_t* grafo = memo_aloca(sizeof(grafo_t));
	grafo->nvertices = 0;
	grafo->vertices = NULL;
	return grafo;
}

/* insere um vértice no grafo */
bool grafo_insere_vertice(grafo_t* g, vertice_t* v){
	g->nvertices++;
	g->vertices = lista_insere_vertice(g->vertices, v);
	return true;
}

/* retorna um vértice associado a uma chave (usar strcmp) */
vertice_t* grafo_busca_vertice(grafo_t* g, char* chave){
	return lista_busca_vertice(g->vertices, chave);
}

/*
 * Insere uma aresta entre os vértices v1 e v2. Como o grafo
 * é não-direcionado, a função deve procurar os dois vértices
 * (função anterior) e inserir um ao outro em sua lista de
 * adjacência (v1 na lista de v2, e v2 na lista de v1).
 */
bool grafo_insere_aresta(grafo_t* g, char* v1, char* v2){
	vertice_insere_aresta(grafo_busca_vertice(g, v1), grafo_busca_vertice(g, v2));
	return true;
}

/* função que imprime vértices e arestas conforme formato */
void grafo_imprime(grafo_t* g){
	lista_t* cpy = g->vertices;
	while(cpy != NULL){
		printf("%s -> ", cpy->vert->chave);
		lista_imprime(cpy->vert->adjacentes);
		printf("\n");
		cpy = cpy->prox;
	}
}

/* destroi e libera memória de um grafo */
void grafo_destroi(grafo_t* g){
	lista_t* cpy = g->vertices;
	while(cpy != NULL){
		cpy = lista_remove_vertice(cpy);
		cpy = cpy->prox;
	}
	memo_libera(g);
}