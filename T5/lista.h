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
#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include "memo.h"

typedef struct _lista{
	struct _lista* next;
	struct _lista* prev;
	char* text;
}lista_t;

typedef struct{
	lista_t* first;
	lista_t* last;
}ptr;

ptr* lista_cria(void);
void lista_destroi(ptr* pointer);
ptr* lista_insere(ptr* pointer, int pos);
lista_t* lista_busca(ptr* pointer, int pos);
ptr* lista_remove(ptr* pointer, int pos);

#endif /* _LISTA_H_ */
