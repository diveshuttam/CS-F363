#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
typedef struct SymbolTable *SymbolTable;

#define MAX_VAR 100
#include "SeqList.h"
#include "hash.h"
#include <stdlib.h>
#define ALPHA_INV 1.33
#define HASH_A 5
#define HASH_B 5183



enum StEntryType{
    VAR_DEC,
    FUNC_DEC,
    REC_DEF,
    REC_DEC,
};

typedef struct StEntry {
    enum StEntryType et;
    void *entry;
} *StEntry;

void insertST(char *key, StEntry value, SymbolTable st);
void* findST(char *key, SymbolTable st);
int getMemoryOfVarInSymbolTable(SymbolTable st);
void setMemoryOfVarInSymbolTable(SymbolTable st,int new_size);
SeqList getListSymbolTable(SymbolTable st);


#endif