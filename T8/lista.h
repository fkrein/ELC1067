#ifndef _LISTA_H_
#define _LISTA_H_

#include "vertice.h"

/* Coloque aqui suas funções de lista para vértices */

struct vertice;

typedef struct lista{
	struct vertice* vert;
	struct lista* prox;
}lista_t;

lista_t* lista_insere_vertice(lista_t* list, vertice_t* v);
struct vertice* lista_busca_vertice(lista_t* list, char* chave);
void lista_imprime(lista_t* list);
lista_t* lista_remove_vertice(lista_t* list);

#endif /* _LISTA_H_ */