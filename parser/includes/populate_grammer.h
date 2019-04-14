#ifndef __POPULATE_GRAMMER_H
#define __POPULATE_GRAMMER_H
#include "filenames.h"
#include "parserDef.h"
#include "hash.h"
void follows(NonTerminal* non_terminals, Terminal* terminals, const char** non_terminals_map, const char **terminals_map, const hashTable ht_non_terminals,const hashTable ht_terminals);
void firsts(NonTerminal* non_terminals, Terminal* terminals, const char** non_terminals_map,const char** terminals_map,const hashTable ht_non_terminals,const hashTable ht_terminals);
grammerRule* grammer(const NonTerminal* non_terminals,const Terminal* terminals,const char** non_terminals_map, const char** terminals_map,const hashTable ht_non_terminals, const hashTable ht_terminals);
char **get_non_terminals_map();
void initialize_tnt(NonTerminal *non_terminals,Terminal *terminals,const char **terminals_map,const char **non_terminals_map,const hashTable ht_terminals,const hashTable ht_non_terminals);
void print_grammer_rule(const grammerRule gr);
void findFirst(NonTerminal* nt,grammerRule* grammerRules, Terminal *eps);
void findFollow(NonTerminal* nt,grammerRule* grammerRules, Terminal *eps, Terminal *dollar);
#endif