/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH   MAX_LINE_LENGTH-2
/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

typedef int16_t hack_addr;
typedef int16_t opcode;

char *extract_label(const char *, char*);

enum instr_type {
	INVALID_INSTRUCTION = -1,
	A-TYPE_INSTRUCTION,
	C-TYPE_INSTRUCTION
}

typedef struct c_instruction {
	opcode a:1;
	opcode comp:6;
	opcode dest:3;
	opcode jump:3;
}

typedef struct a_instruction {
	union {
		hack_addr address,
		char * label;
	}
	bool is_addr;
}

struct instruction {
	union {
		a_instruction,
		c_instruction;
	}
	instr_type type;
}