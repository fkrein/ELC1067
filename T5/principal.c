/*
* principal.c
* Implementação de editor de texto gráfico.
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

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "texto.h"
#include "memo.h"

int main(int argc, char **argv){

	if(argc < 2){
		printf("Too few arguments!\n");
		exit(-1);
	}else if(argc > 2){
		printf("Too many arguments!\n");
		exit(-1);
	}

	FILE *file = fopen(argv[1], "r+");
	if(file == NULL){
		file = fopen(argv[1], "w+");
	}

	texto_t* texto = texto_inicia();
	texto_le_arquivo(texto, argv[1], file);

/* enquanto continua execução */
	while(texto_processa_comandos(texto)){
		texto_atualiza_tela(texto);
	}
	texto_destroi(texto);

	fclose(file);
	memo_relatorio();

	return 0;
}