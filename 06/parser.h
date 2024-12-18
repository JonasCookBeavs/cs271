/****************************************
 * C-ploration 10 for CS 271
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
#include "symtable.h"
#include "error.h"
#include "hack.h"
#ifndef __PARSER_H__
#define __PARSER_H__
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH   MAX_LINE_LENGTH-2
#define MAX_HACK_ADDRESS  INT16_MAX
#define MAX_INSTRUCTIONS  MAX_HACK_ADDRESS
/** function prototypes **/
char *strip(char *s);

typedef int16_t hack_addr;
typedef int16_t opcode;

char *extract_label(const char *, char*);

enum instr_type {
	INVALID_INSTRUCTION = -1,
	ATYPE_INSTRUCTION,
	CTYPE_INSTRUCTION,
};

typedef struct c_instruction {
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;
} c_instruction;

typedef struct a_instruction{
	union {
		hack_addr address;
		char * label;
	}type;
	bool is_addr;
} a_instruction;

typedef struct instruction {
	union {
		a_instruction a;
		c_instruction c;
	} instr;
	enum instr_type type;
} instruction;

int parse(FILE * file, instruction *instructions);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

void add_predefined_smybols();

bool parse_A_instruction(const char *line, a_instruction *instr);

void parse_C_instruction(char *line, c_instruction *instr, int line_num);

void assemble(const char * file_name, instruction* instructions, int num_instructions);

opcode instruction_to_opcode(c_instruction instr);
#endif