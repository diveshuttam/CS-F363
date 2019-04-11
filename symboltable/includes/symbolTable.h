#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
typedef struct SymbolTable *SymbolTable;
SymbolTable createSymbolTable();
void addEntry(SymbolTable st, void *key, void* entry);
#endif