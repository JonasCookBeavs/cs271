/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#define MAX_LINE_NUMBER  200
#define MAX_LABEL_LENGTH  MAX_LINE_LENGTH-2
/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	// your code here
	char s_new[strlen(s)+1];
	int i = 0;
	
	for (char *s2 = s; *s2; s2++){
		if(*s2 == '/' && *(s2+1) == '/'){
			break;
		}
		else if(!isspace(*s2)){
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions){
	unsigned int instNum = 0;
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	char line[MAX_LINE_NUMBER] = {0};
	//char inst_type = 'd';
	
	add_predefined_smybols();
	instruction instr;
	
	char tmp_line[MAX_LINE_LENGTH];
	
	while (fgets(line, sizeof(line), file)) {
		//inst_type = 'd';
		line_num++;
		if(instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		if(!*line){
			continue;
		}
		if(is_Atype(line)){
			//inst_type = 'A';
			instNum++;
			if (!parse_A_instruction(line, &instr.instr.a)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.type = ATYPE_INSTRUCTION;
			if(instr.instr.a.is_addr){				
				printf("A: %d\n", instr.instr.a.type.address);
			} else{
				printf("A: %s\n", instr.instr.a.type.label);
			}
		}
		else if(is_Ctype(line)){
			//inst_type = 'C';
			instNum++;
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.instr.c, line_num);
			instr.type = CTYPE_INSTRUCTION;
			if(instr.instr.c.comp == COMP_INVALID){
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			if(instr.instr.c.dest == DEST_INVALID){
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			if(instr.instr.c.jump == JMP_INVALID){
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			
			printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);

		}
		else if(is_label(line)){
			//inst_type = 'L';
			char label[MAX_LABEL_LENGTH] = {0};
			strcpy(line, extract_label(line, label));
			if(isalpha(label[0]) == 0){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(line, instr_num);
			
			continue;
		}
		//printf("%u: %c  %s\n", instr_num, inst_type, line);
		instructions[instr_num++] = instr;
		
	}
	return instr_num;
}

bool is_Atype(const char *line) {
	return line[0] == '@';
}

bool is_Ctype(const char *line){
	return !is_Atype(line) && !is_label(line);
}

bool is_label(const char *line){
	int i = 0;
	while (line[i] != '\0'){
		i++;
	}
	if(line[0] == '(' && line[i - 1] == ')'){
		return true;
	}
	else {
		return false;
	}
}

char *extract_label(const char *line, char* label){
	//int i = 0;
	//while (line[i] != ')'){
	//	i++;
	//}
	//strncpy(label, line+1, i-1);
	//label[i-1] = '\0';
	//return label;
	int i = 0;
	for (const char *s = line; *s; s++){
		if (*s== '(' || *s== ')'){
			continue;
		} else {
			label[i++] = *s;
		}
	}
	return label;
}

void add_predefined_smybols(){
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		struct predefined_symbol sym = predefined_symbols[i];
		symtable_insert(sym.name, sym.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = (char*)malloc(strlen(line));
    strcpy(s, line+1);
    char *s_end = NULL;
    
    long result = strtol(s, &s_end, 10);

    //printf("label: %s\n", s_end);

    if (s == s_end){
        instr->type.label = (char*)malloc(strlen(line));
        strcpy(instr->type.label, s);
        instr->is_addr = false;
        //printf("str %s\n", instr->operand.label);    
    //}else if (errno == 0 && *s_end != 0){
    }else if (*s_end != 0){
        return false;
    }else{
        instr->type.address = result;
        instr->is_addr = true;
    }
    return true;
}

void parse_C_instruction(char *line, c_instruction *instr, int line_num){
	char *token;
	char *jump;
	char *dest;
	char *comp;
	
	token = strtok(line, ";");
	jump = strtok(NULL, ";");
	
	dest = strtok(token, "=");
	comp = strtok(NULL, "=");
	
	if(comp == NULL){
		comp = dest;
		dest = NULL;
	}
	
	int a;
	instr->jump = jump ? str_to_jumpid(jump) : JMP_NULL;
	instr->dest = dest ? str_to_destid(dest) : DEST_NULL;
	instr->comp = str_to_compid(comp, &a);
	instr->a = a;
	
	
}