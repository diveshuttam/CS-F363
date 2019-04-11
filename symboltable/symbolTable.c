#include "symbolTable.h"
#include "hash.h"
#include "stdio.h"
#define ALPHA_INV 1.33
#define HASH_A 5
#define HASH_B 5183

struct SymbolTable {
    int size;
    hashTable ht;
};

//currentSymbolTable
static SymbolTable cST;
//global symbol table
static SymbolTable gST;

SymbolTable getCurrentSymbolTable(){
    return cST;
}

SymbolTable globalSymbolTable(){
    return gST;
}

int getSize(SymbolTable st){
    return st->size;
}

SymbolTable createSymbolTable(){
    if(gST==NULL){
        gST=malloc(sizeof(struct SymbolTable));
        gST->ht=newHashTable(MAX_FUN,HASH_A,HASH_B);
        gST->size=0;
    }
}