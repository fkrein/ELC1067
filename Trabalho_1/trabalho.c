#include <stdio.h>
#include <string.h>
#define TNOME 50
#define QTDD_MAX 50

void alunos();
//Lê o arquivo "alunos.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_alunos" e salva dentro dele as matrículas
//Recebe a matriz "nomes" e salva dentro dela os nomes

void notas();
//Lê o arquivo "notas.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_notas" e salva dentro dele as matrículas
//Recebe o vetor "medias" e salva dentro dele as médias das notas

void busca();
//Busca um nome dentro do vetor "nomes" e salva sua matrícula
//Busca essa matrícula em "mat_notas" e imprime o nome e a nota

int main(int argc, char *argv[]){

    int mat_alunos[QTDD_MAX] = {0};
    int mat_notas[QTDD_MAX] = {0};
    float medias[QTDD_MAX] = {0};
    char nomes[QTDD_MAX][TNOME];

    if(argc>1){
        alunos();
        notas();
        busca();
    }else{
        printf("Parametro de busca nao especificado!");
    }

    return 0;

}

void alunos(){

}

void notas(){

}

void busca(){

}
