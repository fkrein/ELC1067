#include <stdbool.h>
#include "lista.h"
#include "vertice.h"

typedef struct{
	lista_t* first;
	lista_t* last;
}fila_t;

fila_t* fila_cria(void);
fila_t* fila_insere(fila_t* Q, vertice_t* s);
bool fila_vazia(fila_t* Q);
vertice_t* fila_remove(fila_t* Q);