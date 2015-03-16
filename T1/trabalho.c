#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TNOME 50
#define QTDD_MAX 50
#define ALUNOS "alunos.txt"
#define NOTAS "notas.txt"

void alunos(int mat_alunos[], char nomes[][TNOME]);
//L� o arquivo "alunos.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_alunos" e salva dentro dele as matr�culas
//Recebe a matriz "nomes" e salva dentro dela os nomes

void notas(int mat_notas[], float medias[]);
//L� o arquivo "notas.txt" e salva os dados dele em vetores
//Recebe o vetor "mat_notas" e salva dentro dele as matr�culas
//Recebe o vetor "medias" e salva dentro dele as m�dias das notas

void busca(int mat_alunos[], char nomes[][TNOME], int mat_notas[], float medias[], char pesquisa[]);
//Busca um nome dentro do vetor "nomes" e salva sua matr�cula
//Busca essa matr�cula em "mat_notas" e imprime o nome e a nota

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
        strcpy(pesquisa, strupr(pesquisa));
        busca(mat_alunos,nomes,mat_notas,medias,pesquisa);
    }else{
        printf("Parametro de busca nao especificado!");
    }

    return 0;

}

void alunos(int mat_alunos[], char nomes[][TNOME]){

    int cont=0, i, mat;
    char c='\n';
    FILE *ptr = fopen(ALUNOS,"r");

    if(ptr == NULL){
        printf("Caminho de arquivo invalido!");
        fclose(ptr);
        exit(0);
    }else{
        while(feof(ptr)==0){
            if(fscanf(ptr,"%d",&mat) != 1){
                printf("Arquivo invalido!");
                fclose(ptr);
                exit(0);
            }

            mat_alunos[cont]=mat;
            c=fgetc(ptr);
            while(c==' '){
                c=fgetc(ptr);
            }
            i = 0;
            while(c!='\n' && c!=EOF){
                nomes[cont][i]=toupper(c);
                if((nomes[cont][i]<'A' || nomes[cont][i]>'Z') && nomes[cont][i] != ' ' && nomes[cont][i] != '-'){
                    printf("Nome no arquivo errado!");
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
    mat_alunos[cont] = -1;
    fclose(ptr);

}

void notas(int mat_notas[], float medias[]){

    int cont=0;
    float nota1, nota2;
    FILE *ptr = fopen(NOTAS,"r");
    if(ptr == NULL){
        printf("Caminho de arquivo invalido!");
        fclose(ptr);
        exit(0);
    }else{
        while(feof(ptr)==0){
            if(fscanf(ptr,"%d %f %f ",&mat_notas[cont],&nota1,&nota2) != 3){
                printf("Arquivo invalido!");
                fclose(ptr);
                exit(0);
            }
            medias[cont++]=(nota1+nota2)/2;
        }
    }
    mat_notas[cont] = -1;
    fclose(ptr);

}

void busca(int mat_alunos[], char nomes[][TNOME], int mat_notas[], float medias[], char pesquisa[]){

    int i=0,j;
    while(mat_alunos[i] != -1){
        if(strstr(nomes[i],pesquisa) != NULL){
            j=0;
            while(mat_notas[j] != -1){
                if(mat_alunos[i]==mat_notas[j]){
                    printf("%.2f %s\n",medias[j],nomes[i]);
                }
                j++;
            }
        }
        i++;
    }

}
