#ifndef __POPULATE_GRAMMER_H
#define __POPULATE_GRAMMER_H
#include "parserDef.h"
#include "hash.h"
void follows(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char **terminals_map, hashTable ht_non_terminals,hashTable ht_terminals);
void firsts(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char** terminals_map,hashTable ht_non_terminals, hashTable ht_terminals);
grammerRule* grammer(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char** terminals_map,hashTable ht_non_terminals, hashTable ht_terminals);
char **get_non_terminals_map();
void initialize_tnt(NonTerminal *non_terminals,Terminal *terminals,char **terminals_map,char **non_terminals_map,hashTable ht_terminals,hashTable ht_non_terminals);

#endif