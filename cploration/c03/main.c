/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH  200
int main(int argc, const char *argv[])
{	
	if(argc != 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	FILE *fin = fopen( argv[1], "r" );
	
	if (fin == NULL){
		perror("Unable to open file!");
		exit(EXIT_FAILURE);	
	}
	
	char out_file[MAX_LINE_LENGTH];
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo");
	FILE *fout = fopen(out_file, "w+");
	
	return 1;
}