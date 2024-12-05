/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef __ERROR_H__
#define __ERROR_H__

enum exitcode {
		EXIT_INCORRECT_ARGUMENTS,
		EXIT_CANNOT_OPEN_FILE,
		EXIT_TOO_MANY_INSTRUCTIONS,
		EXIT_INVALID_LABEL,
		EXIT_SYMBOL_ALREADY_EXISTS,
		EXIT_INVALID_A_INSTR,
		EXIT_INVALID_C_DEST,
		EXIT_INVALID_C_COMP,
		EXIT_INVALID_C_JUMP,
};

void exit_program(enum exitcode code, ...);

#endif