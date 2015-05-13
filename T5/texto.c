/*
 * texto.c
 * Funções para implementação de editor de texto.
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "texto.h"
#include "tela.h"
#include "memo.h"
#include "lista.h"

enum { nada, editando } estado;

texto_t* texto_inicia(void){
	texto_t* t = (texto_t*)memo_aloca(sizeof(texto_t));
	tamanho_t tam = { 600, 400 };	/* tamanho da tela */
	
	tela_inicializa(&t->tela, tam, "Editor Supremo");
	tela_limpa(&t->tela);

	t->linhas = lista_cria();
	t->nlin = 0;
	t->lincur = 0;
	t->colcur = 0;
	t->lin1 = 0;
	t->col1 = 0;

	/* inicialize aqui quaisquer outras estruturas, como a lista de linhas */

	return t;
}

void texto_destroi(texto_t* txt){
	while(txt->linhas->first != txt->linhas->last){
		txt->linhas = lista_remove(txt->linhas, 1);
	}
	tela_limpa(&txt->tela);
	tela_finaliza(&txt->tela);
	lista_destroi(txt->linhas);
	memo_libera(txt);
}

tela_t* texto_tela(texto_t* txt){
	assert( txt != NULL );
	return &txt->tela;
}

void texto_desenha_cursor_tela(texto_t *txt){
	cor_t preto = {255.0, 255.0, 0.0};
	tamanho_t tt;
	ponto_t pt1, pt2;

	char* texto = lista_busca(txt->linhas, txt->lincur+1)->text;
	char subtexto[60];
	strncpy(subtexto, texto, txt->colcur);
	subtexto[txt->colcur] = '\0';
	tt = tela_tamanho_texto(&txt->tela, subtexto);

	pt1.x = tt.larg + 1;
	pt1.y = txt->lincur * tt.alt;
	pt2.x = pt1.x;
	pt2.y = pt1.y + tt.alt;
	tela_cor(&txt->tela, preto);
	tela_linha(&txt->tela, pt1, pt2);
}

void texto_desenha_tela(texto_t *txt){
	cor_t cor;
	char *texto;
	tamanho_t tt;
	ponto_t pt;
	int i;
	
	/* limpa a tela. Comentar se ficar lento */
	tela_limpa(&txt->tela);

	cor.r = 0;
	cor.g = 255;
	cor.b = 0;
	tela_cor(&txt->tela, cor);
	
	for(i = 1; i <= txt->nlin; i++){
		texto = lista_busca(txt->linhas, i)->text;
		tt = tela_tamanho_texto(&txt->tela, texto);

		pt.x = 1;
		pt.y = (i - 1)*tt.alt + 1;

		tela_texto(&txt->tela, pt, texto);
	}

	texto_desenha_cursor_tela(txt);
}

void texto_atualiza_tela(texto_t *txt){
	texto_desenha_tela(txt);
	tela_mostra(texto_tela(txt));
	tela_espera(30);
}

bool texto_processa_comandos(texto_t* txt, char* arq){
	int i, j;
	int tecla = tela_tecla(texto_tela(txt));
	int tecla2 = tela_tecla2(texto_tela(txt));
	int modificador = tela_tecla_modificador(texto_tela(txt));
	if( tecla == ALLEGRO_KEY_Q && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
		return false;
	}else if( tecla == ALLEGRO_EVENT_DISPLAY_CLOSE){
		return false;
	}else if( tecla == ALLEGRO_KEY_S && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
		estado = nada;
		FILE* file = fopen(arq, "w+");
		for(i = 1; i <= txt->nlin; i++){
			for(j = 0; j < strlen(lista_busca(txt->linhas, i)->text); j++){
				fputc(lista_busca(txt->linhas, i)->text[j], file);
			}
			if(i != txt->nlin){
				fputc('\n', file);
			}
		}
		fclose(file);
	}else if( tecla == ALLEGRO_KEY_E && (modificador & ALLEGRO_KEYMOD_CTRL) ) {
		estado = editando;
	}else if( tecla2 == ALLEGRO_KEY_LEFT ){
		texto_move_esq(txt);
	}else if( tecla2 == ALLEGRO_KEY_RIGHT ){
		texto_move_dir(txt);
	}else if( tecla2 == ALLEGRO_KEY_UP ){
		texto_move_cima(txt);
	}else if( tecla2 == ALLEGRO_KEY_DOWN ){
		texto_move_baixo(txt);
	}else if(estado == editando){
		if( tecla == 8 ){
			texto_remove_char(txt);
		}else if(tecla >= 1){
			texto_insere_char(txt, tecla);
		}
	}

	return true;
}

void texto_move_esq(texto_t *txt){
	if(txt->colcur > 0){
		txt->colcur--;
	}else if(txt->lincur > 0){
		txt->lincur--;
		txt->colcur = strlen(lista_busca(txt->linhas, txt->lincur+1)->text);
	}
}

void texto_move_dir(texto_t *txt){
	if(txt->colcur < strlen(lista_busca(txt->linhas, txt->lincur+1)->text)){
		txt->colcur++;
	}else if(txt->colcur == strlen(lista_busca(txt->linhas, txt->lincur+1)->text)){
		if(txt->lincur < txt->nlin-1){
			txt->lincur++;
			txt->colcur = 0;
		}
	}
}

void texto_move_baixo(texto_t *txt){
	if(txt->lincur < txt->nlin-1){
		txt->lincur++;
	}
	if(txt->colcur > strlen(lista_busca(txt->linhas, txt->lincur+1)->text)){
		txt->colcur = strlen(lista_busca(txt->linhas, txt->lincur+1)->text);
	}
}

void texto_move_cima(texto_t *txt){
	if(txt->lincur > 0){
		txt->lincur--;
	}
	if(txt->colcur > strlen(lista_busca(txt->linhas, txt->lincur+1)->text)){
		txt->colcur = strlen(lista_busca(txt->linhas, txt->lincur+1)->text);
	}
}

void texto_insere_char(texto_t *txt, char c){
	int i;
	if(c != '\r'){
		lista_busca(txt->linhas, txt->lincur + 1)->text = memo_realoca
		(lista_busca(txt->linhas, txt->lincur + 1)->text, strlen(lista_busca(txt->linhas, txt->lincur + 1)->text)+1);
		for(i = strlen(lista_busca(txt->linhas, txt->lincur + 1)->text); i > txt->colcur; i--){
			lista_busca(txt->linhas, txt->lincur + 1)->text[i] = lista_busca(txt->linhas, txt->lincur + 1)->text[i-1];
		}
		lista_busca(txt->linhas, txt->lincur + 1)->text[txt->colcur] = c;
		txt->colcur++;
	}else{
		txt->linhas = lista_insere(txt->linhas, txt->lincur+2);
		lista_busca(txt->linhas, txt->lincur+2)->text = memo_realoca(lista_busca(txt->linhas, txt->lincur+2)->text,
		strlen(lista_busca(txt->linhas, txt->lincur+1)->text) - txt->colcur*sizeof(char));
		for(i = txt->colcur; i < strlen(lista_busca(txt->linhas, txt->lincur+1)->text); i++){
			lista_busca(txt->linhas, txt->lincur+2)->text[i-txt->colcur] = lista_busca(txt->linhas, txt->lincur+1)->text[i];
		}
		lista_busca(txt->linhas, txt->lincur+1)->text = 
		memo_realoca(lista_busca(txt->linhas, txt->lincur+1)->text,	(txt->colcur + 1)*sizeof(char));
		lista_busca(txt->linhas, txt->lincur+1)->text[txt->colcur+1] = '\0';
	}
}

void texto_remove_char(texto_t *txt){

}

void texto_le_arquivo(texto_t *txt, char *nome){

	txt->nome = nome;
	char c;
	int col=0, lin=1;

	FILE *file = fopen(nome, "r+");
	if(file == NULL){
		file = fopen(nome, "w+");
	}

	txt->linhas = lista_insere(txt->linhas, 1);

	while((c = fgetc(file)) != EOF){
		if(c == '\n'){
			col = 0;
			lin++;
			txt->linhas = lista_insere(txt->linhas, lin);
		}else{
			lista_busca(txt->linhas, lin)->text = 
			memo_realoca(lista_busca(txt->linhas, lin)->text, strlen(lista_busca(txt->linhas, lin)->text)+2*sizeof(char));
			lista_busca(txt->linhas, lin)->text[col] = c;
			lista_busca(txt->linhas, lin)->text[col+1] = '\0';
			col++;
		}
	}

	txt->nlin = lin;
	fclose(file);
}