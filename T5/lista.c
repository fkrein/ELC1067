/*
 * lista.h
 * Funções de TAD lista duplamente encadeada.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. F. Lima, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lista.h"
#include "memo.h"

ptr* lista_cria(void){

	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->text = (char*) memo_aloca(sizeof(char));
	novo->text[0] = -1;
	novo->prev = NULL;
	novo->next = NULL;

	ptr* pointer = (ptr*) memo_aloca(sizeof(ptr));
	pointer->first = novo;
	pointer->last = novo;

	return pointer;

}

void lista_destroi(ptr* pointer){

	memo_libera(pointer->first->text);
	memo_libera(pointer->first);
	memo_libera(pointer);

}

ptr* lista_insere(ptr* pointer, int pos){

	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->text = (char*) memo_aloca(sizeof(char));
	novo->text[0] = '\0';
	if(pos == 1){
		novo->prev = NULL;
		novo->next = pointer->first;
		pointer->first->prev = novo;
		pointer->first = novo;
	}else{
		novo->prev = lista_busca(pointer, pos-1);
		novo->next = lista_busca(pointer, pos-1)->next;
		if(lista_busca(pointer, pos-1)->next != NULL){
			lista_busca(pointer, pos-1)->next->prev = novo;
		}else{
			pointer->last = novo;
		}
		lista_busca(pointer, pos-1)->next = novo;
	}
	return pointer;

}

lista_t* lista_busca(ptr* pointer, int pos){

	int i;
	lista_t* p = pointer->first;
	for(i = 1; i < pos; i++){
		p = p->next;
	}
	return p;
	
}

ptr* lista_remove(ptr* pointer, int pos){
	
	lista_t* p = lista_busca(pointer, pos);
	if(p->next != NULL){
		p->next->prev = p->prev;
	}else{
		pointer->last = p->prev;
	}
	if(p->prev != NULL){
		p->prev->next = p->next;
	}else{
		pointer->first = p->next;
	}
	memo_libera(p->text);
	memo_libera(p);
	return pointer;

}