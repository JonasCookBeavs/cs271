/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Jonas Cook
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "symtable.h"
#define SYMBOL_TABLE_SIZE 1000

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hashCode(hack_addr addr) {
   return addr %= SYMBOL_TABLE_SIZE;
}

int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash %= SYMBOL_TABLE_SIZE;
}
	
void symtable_insert(char* name, hack_addr addr) {

   struct Symbol *item = (struct Symbol*)malloc(sizeof(struct Symbol));
   item->addr = addr;  
   item->name = strdup(name);

   //get the hash 
   int hashIndex = hash(name);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      ++hashIndex;
      hashIndex %= SYMBOL_TABLE_SIZE;
   }
   hashArray[hashIndex] = item;
}

struct Symbol* symtable_find(char* key){
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
		if(hashArray[i] != NULL && strcmp(key, hashArray[i]->name) == 0){
			return hashArray[i];
		}
	}
	return NULL;
}

void symbol_display_table() {
   int i = 0;
	
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->addr);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}

void symtable_print_labels() {   
    int i = 0;
    for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
} 