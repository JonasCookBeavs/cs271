/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#define MAX_LINE_NUMBER  200
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
void parse(FILE * file){
	char line[MAX_LINE_NUMBER] = {0};
	char inst_type = 'd';
	while (fgets(line, sizeof(line), file)) {
		inst_type = 'd';
		strip(line);
		if(!*line){
			continue;
		}
		if(is_Atype(line)){
			inst_type = 'A';
		}
		else if(is_label(line)){
			inst_type = 'L';
		}
		else {
			inst_type = 'C';
		}
		printf("%c  %s\n", inst_type, line);
	}
	
}

bool is_Atype(const char *line) {
	return line[0] == '@';
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