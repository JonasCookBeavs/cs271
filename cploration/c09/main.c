/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
int main(int argc, const char *argv[])
{		

	// your code here
	if(argc != 2){
		// incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);  
	}		
	FILE *fin = fopen( argv[1], "r" );
	if (fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	parse(fin);
	symtable_print_labels();
	fclose(fin);
}


