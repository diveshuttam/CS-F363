#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
typedef struct SymbolTable *SymbolTable;

#define MAX_FUN 20
#define MAX_VAR 100

SymbolTable createSymbolTable();
void addEntry(SymbolTable st, void *key, void* entry);
SymbolTable getCurrentSymbolTable();
SymbolTable getGlobalSymbolTable();
int getSizeSymbolTable(SymbolTable st);
void addCSTtoGST(char *fun_name);
#endif