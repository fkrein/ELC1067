#include "pilha.h"
#include "memo.h"

pilha_t *pilha_cria(void){
	pilha_t* pilha = (pilha_t*) malloc(sizeof(pilha_t));
	pilha->topo = NULL;
	return pilha;
}

void pilha_destroi(pilha_t* p){
	memo_libera(p);
}

bool pilha_vazia(pilha_t* p){
	return p == NULL;
}

void pilha_insere(pilha_t* p, arv_t* arv){
	fila* novo = (fila*) memo_aloca(sizeof(fila));
	novo->arv = arv;
	novo->prox = p->topo;
	p->topo = novo;
}

arv_t* pilha_remove(pilha_t* p){
	arv_t* removido = p->topo->arv;
	fila* cpy = p->topo;
	p->topo = p->topo->prox;
	memo_libera(cpy);
	return removido;
}