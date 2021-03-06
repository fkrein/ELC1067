#include <stdio.h>
#include "grafo.h"
#include "fila.h"
#include "vertice.h"

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

void grafo_busca_largura(grafo_t* G, vertice_t* s){
	lista_t* cpy = G->vertices;
	vertice_t* u;
	lista_t* v;
	while(cpy != NULL){
		cpy->vert->cor = BRANCO;
		cpy = cpy->prox;
	}
	fila_t* Q = fila_cria();
	Q = fila_insere(Q, s);
	while(!fila_vazia(Q)){
		u = fila_remove(Q);
		v = u->adjacentes;
		while(v != NULL){
			if(v->vert->cor == BRANCO){
				v->vert->cor = CINZA;
				v->vert->distancia = u->distancia + 1;
				v->vert->ant = u;
				Q = fila_insere(Q, v->vert);
			}
			v = v->prox;
		}
		u->cor = PRETO;
	}
	fila_destroi(Q);
}

void grafo_caminho_curto(grafo_t* G, char* fonte, char* destino){
	vertice_t* s = grafo_busca_vertice(G, fonte);
	vertice_t* v = grafo_busca_vertice(G, destino);
	if(s == v){
		printf("%s -> ", s->nome);
		return;
	}
	if(v->ant == NULL){
		printf("Nao existe caminho de %s a %s\n", s->nome, v->nome);
	} else {
		grafo_caminho_curto( G, fonte, v->ant->chave );
		printf("%s -> ", v->nome);
	}
}