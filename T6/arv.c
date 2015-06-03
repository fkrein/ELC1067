#include <stdio.h>
#include "arv.h"
#include "memo.h"

arv_t* arv_cria(op_t op){
	arv_t* novo = (arv_t*) memo_aloca(sizeof(arv_t));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->dado = op;
	return novo;
}

arv_t* arv_insere_esquerda(arv_t* arv, arv_t* novo){
	arv->esq = novo;
	return arv;
}

arv_t* arv_insere_direita(arv_t* arv, arv_t* novo){
	arv->dir = novo;
	return arv;
}

void arv_imprime_pre_ordem(arv_t* arv){
	if(arv != NULL){
		if(arv->dado.tipo == OPERADOR){
			printf("%c ", arv->dado.u.operador);
		}else{
			printf("%.2f ", arv->dado.u.operando);
		}
		arv_imprime_pre_ordem(arv->esq);
		arv_imprime_pre_ordem(arv->dir);
	}
}

void arv_imprime_em_ordem(arv_t* arv){
	if(arv != NULL){
		printf("(");
		arv_imprime_em_ordem(arv->esq);
		if(arv->dado.tipo == OPERADOR){
			printf("%c", arv->dado.u.operador);
		}else{
			printf("%.2f", arv->dado.u.operando);
		}
		arv_imprime_em_ordem(arv->dir);
		printf(")");
	}
}

void arv_imprime_pos_ordem(arv_t* arv){
	if(arv != NULL){
		arv_imprime_pos_ordem(arv->esq);
		arv_imprime_pos_ordem(arv->dir);
		if(arv->dado.tipo == OPERADOR){
			printf("%c ", arv->dado.u.operador);
		}else{
			printf("%.2f ", arv->dado.u.operando);
		}
	}
}

void arv_destroi(arv_t* arv){
	if(arv != NULL){
		arv_destroi(arv->esq);
		arv_destroi(arv->dir);
		memo_libera(arv);
	}
}