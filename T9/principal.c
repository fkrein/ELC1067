#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "vertice.h"

#define TAM_CHAVE 3
#define TAM_NOME 50

int main(int argc, char* argv[]){

	int fvertices, farestas, cont = 0;
	char fv1[TAM_CHAVE + 1];
	char fv2[TAM_CHAVE + 1];
	vertice_t* vert;

	if(argc < 4){
		printf("Too few arguments!\n");
		exit(1);
	}else if(argc > 4){
		printf("Too many arguments!\n");
		exit(1);
	}

	grafo_t* grafo = grafo_cria();

	FILE *file = fopen(argv[1], "r+");
	if(file == NULL){
		printf("Program failed to read file!\n");
		exit(2);
	}

	fscanf(file,"%d %d\n", &fvertices, &farestas);
	while(!feof(file)){
		if(cont < fvertices){
			vert = memo_aloca(sizeof(vertice_t));
			vert->adjacentes = NULL;
			vert->chave = memo_aloca( TAM_CHAVE + 1 );
			vert->nome = memo_aloca( TAM_NOME + 1 );
			fscanf(file, "%s %[^\n]s\n", vert->chave, vert->nome);
			grafo_insere_vertice(grafo, vert);
		}else{
			fscanf(file, "%s %s\n", fv1, fv2);
			grafo_insere_aresta(grafo, fv1, fv2);
		}
		cont++;
	}
	grafo_imprime(grafo);

	printf("\n");
	vert = grafo_busca_vertice(grafo, argv[2]);
	grafo_busca_largura(grafo, vert);
	grafo_caminho_curto(grafo, argv[2], argv[3]);
	printf("( %d cidades de distancia )", grafo_busca_vertice(grafo, argv[3])->distancia);

	grafo_destroi(grafo);

	fclose(file);

	printf("\n");
	memo_relatorio();

	exit(0);
}