#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
#include "parserDef.h"
#include "SeqList.h"
#define INT_SIZE 2
#define REAL_SIZE 4
typedef struct SymbolTable *SymbolTable; 
extern SymbolTable GlobalSymbolTable;
extern SymbolTable CurrentSymbolTable;
struct SymbolTable {
    int size;
    int num_entires;
    hashTable ht;
    SeqList sl;
    char *st_name; //name of the symbol table
    SymbolTable parent;
};
SymbolTable genSymbolTable(Tree ast);
SymbolTable genSymbolTableFromFile(char *filename);
void printSymbolTableFromFile(char *filename);
#endif