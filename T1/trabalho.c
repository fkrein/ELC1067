#include <stdio.h>
#include <string.h>
#define TNOME 50
#define QTDD_MAX 50
#define ALUNOS "alunos.txt"
#define NOTAS "notas.txt"

void alunos(int mat_alunos[], char nomes[][TNOME]);
//Lê o arquivo "alunos.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_alunos" e salva dentro dele as matrículas
//Recebe a matriz "nomes" e salva dentro dela os nomes

void notas(int mat_notas[], float medias[]);
//Lê o arquivo "notas.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_notas" e salva dentro dele as matrículas
//Recebe o vetor "medias" e salva dentro dele as médias das notas

void busca(int mat_alunos[], char nomes[][TNOME], int mat_notas[], float medias[], char pesquisa[]);
//Busca um nome dentro do vetor "nomes" e salva sua matrícula
//Busca essa matrícula em "mat_notas" e imprime o nome e a nota

int main(int argc, char *argv[]){

    int mat_alunos[QTDD_MAX] = {0};
    int mat_notas[QTDD_MAX] = {0};
    float medias[QTDD_MAX] = {0};
    char nomes[QTDD_MAX][TNOME];
    char pesquisa[TNOME];

    char *ch_ptr;
    int i, len=0;
    for(i=1;i<argc;i++){
        ch_ptr = argv[i];
        strcpy(&pesquisa[len],ch_ptr);
        len += strlen(ch_ptr);
        if(i!=(argc-1)){
            pesquisa[len]=' ';
            len++;
        }
    }

    if(argc>1){
        alunos(mat_alunos,nomes);
        notas(mat_notas,medias);
        busca(mat_alunos,nomes,mat_notas,medias,pesquisa);
    }else{
        printf("Parametro de busca nao especificado!");
    }

    return 0;

}

void alunos(int mat_alunos[], char nomes[][TNOME]){

    int cont=0, i;
    char c='\n';
    FILE *ptr = fopen(ALUNOS,"r");
    if(ptr == NULL){
        printf("Caminho de arquivo invalido!");
        fclose(ptr);
        exit(0);
    }else{
        while(feof(ptr)==0){
            if(fscanf(ptr,"%d",&mat_alunos[cont]) == 0){
                printf("Arquivo invalido!");
                fclose(ptr);
                exit(0);
            }
            c=fgetc(ptr);
            while(c==' '){
                c=fgetc(ptr);
            }
            i = 0;
            while(c!='\n' && c!=EOF){
                nomes[cont][i]=toupper(c);
                if(nomes[cont][i]<'A' || nomes[cont][i]>'Z'){
                    printf("Nome invalido!");
                    fclose(ptr);
                    exit(0);
                }
                c=fgetc(ptr);
                i++;
            }
            nomes[cont][i]='\0';
            cont++;
        }
    }
    fclose(ptr);
}

void notas(int mat_notas[], float medias[]){

}

void busca(int mat_alunos[], char nomes[][TNOME], int mat_notas[], float medias[], char pesquisa[]){

}
