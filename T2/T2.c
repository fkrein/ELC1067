#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TNOME 50
#define QTDD_MAX 50
#define ALUNOS "alunos.txt"
#define NOTAS "notas.txt"

void alunos(int *mat_alunos, char **nomes);
//Lê o arquivo "alunos.txt" e salva os dados dele
//Recebe o vetor "mat_alunos" e salva dentro dele as matrículas lidas
//Recebe a matriz "nomes" e salva dentro dela os nomes lidos

void notas(int *mat_notas, float *medias);
//Lê o arquivo "notas.txt" e salva os dados dele
//Recebe o vetor "mat_notas" e salva dentro dele as matrículas lidas
//Recebe o vetor "medias" e salva dentro dele as médias das notas lidas

void busca(int *mat_alunos, char **nomes, int *mat_notas, float *medias, char *pesquisa);
//Recebe 4 vetores contendo as matrículas, nomes e notas dos alunos
//Recebe o vetor "pesquisa" e executa uma busca de seu conteúdo dentor do vetor "nomes"
//Imprime os valores do vetor "medias" seguidos dos respectivos nomes

int main(int argc, char *argv[]){

    int i;
    int *mat_alunos = (int*) malloc(QTDD_MAX*sizeof(int));
    int *mat_notas = (int*) malloc(QTDD_MAX*sizeof(int));
    float *medias = (float*) malloc(QTDD_MAX*sizeof(float));
    char **nomes = (char**) malloc(QTDD_MAX*sizeof(char*));
    char pesquisa[TNOME];
    char *ch_ptr;
    int len=0;

    for(i=0;i<QTDD_MAX;i++){
        mat_alunos[i]=0;
    }
    for(i=0;i<QTDD_MAX;i++){
        mat_notas[i]=0;
    }
    for(i=0;i<QTDD_MAX;i++){
        nomes[i] = (char*) malloc(TNOME*sizeof(char));
    }

    for(i=1;i<argc;i++){
        ch_ptr = argv[i];
        strcpy(&pesquisa[len],ch_ptr);
        len += strlen(ch_ptr);
        if(i!=(argc-1)){
            pesquisa[len]=' ';
            len++;
        }
    }

    for(i=0;i<strlen(pesquisa);i++){
        if((pesquisa[i]<'A' || (pesquisa[i]>'Z' && pesquisa[i]<'a') || pesquisa[i]>'z') && (pesquisa[i]!=' ' && pesquisa[i]!='-')){
            printf("Parametro invalido!");
            exit(0);
        }
    }

        alunos(mat_alunos,nomes);
        notas(mat_notas,medias);
        strcpy(pesquisa, pesquisa);
        busca(mat_alunos,nomes,mat_notas,medias,pesquisa);

    return 0;

}

void alunos(int *mat_alunos, char **nomes){

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
                nomes[cont][i]=c;
                if((nomes[cont][i]<'A' || (nomes[cont][i]>'Z' && nomes[cont][i]<'a') || nomes[cont][i]>'z') && (nomes[cont][i]!=' ' && nomes[cont][i]!='-')){
                    printf("Arquivo Invalido!");
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

void notas(int *mat_notas, float *medias){

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
    fclose(ptr);

}

void busca(int *mat_alunos, char **nomes, int *mat_notas, float *medias, char *pesquisa){

    int i=0,j,upr;
    char upr_nomes[TNOME];
    char upr_pesquisa[TNOME];
    strcpy(upr_pesquisa,pesquisa);
    strupr(upr_pesquisa);
    while(mat_alunos[i] != 0){
        strcpy(upr_nomes,nomes[i]);
        strupr(upr_nomes);
        if(strstr(upr_nomes,upr_pesquisa) != NULL){
            j=0;
            while(mat_notas[j] != 0){
                if(mat_alunos[i]==mat_notas[j]){
                    printf("%.2f %s\n",medias[j],nomes[i]);
                }
                j++;
            }
        }
        i++;
    }

}
