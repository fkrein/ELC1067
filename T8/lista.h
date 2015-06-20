#ifndef _LISTA_H_
#define _LISTA_H_

#include "vertice.h"

/* Coloque aqui suas funções de lista para vértices */

struct vertice;

typedef struct lista{
	struct vertice* vert;
	struct lista* prox;
}lista_t;

#endif /* _LISTA_H_ */