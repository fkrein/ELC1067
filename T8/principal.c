#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	if(argc < 2){
		printf("Too few arguments!\n");
		exit(1);
	}else if(argc > 2){
		printf("Too many arguments!\n");
		exit(1);
	}

	FILE *file = fopen(argv[1], "r+");
	if(file == NULL){
		printf("Program failed to read file!\n");
		exit(2);
	}

	fclose(file);

	exit(0);
}