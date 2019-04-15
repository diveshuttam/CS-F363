#ifndef __SYMBOL_TABLE_UTILS_H
#define __SYMBOL_TABLE_UTILS_H
typedef struct SymbolTable *SymbolTable;

#define MAX_VAR 100
#include "SeqList.h"
#include "hash.h"
#include <stdlib.h>
#include "parserDef.h"

#define ALPHA_INV 1.33
#define HASH_A 5
#define HASH_B 5183

enum StEntryType{
    VAR_DEC,
    FUN_DEF,
    REC_DEF,
    REC_DEC,
};

typedef struct StEntry {
    enum StEntryType et;
    char *et_name;
    int size;
    void *var_entry;
} *StEntry;

void insertST(char *key, StEntry value, SymbolTable st);
void* findST(char *key, SymbolTable st);
int getMemoryOfVarInSymbolTable(SymbolTable st);
void setMemoryOfVarInSymbolTable(SymbolTable st,int new_size);
SymbolTable createST();
SeqList getListSymbolTable(SymbolTable st);
void printST(SymbolTable st);

//get and set GlobalSymbolTable
SymbolTable getGST();
void setGST(SymbolTable st);

//get and set current SymbolTable
SymbolTable getCST();
void setCST(SymbolTable st);
#endif