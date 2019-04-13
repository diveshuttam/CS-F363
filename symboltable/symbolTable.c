#include "symbolTable.h"
#include "stdio.h"

#include <stdlib.h>

struct SymbolTable {
    int size;
    hashTable ht;
    SeqList sl;
};

SymbolTable createST(){
    SymbolTable st=malloc(sizeof(struct SymbolTable));
    st->ht=newHashTable(MAX_VAR*ALPHA_INV, HASH_A,HASH_B);
    st->sl=newList();
    return st;
}

void insertST(char *key, StEntry value, SymbolTable st){
    if(st==NULL)
    {
        st=createST();
    }
    insert(key,value,st->ht);
}


void* findST(char *key, SymbolTable st){
    if(st==NULL){
        return NULL;
    }
    return findHT(key,st->ht);
}

void setMemoryOfVarInSymbolTable(SymbolTable st,int new_size)
{
    if(st==NULL){
        return;
    }
    st->size=new_size;
}

int getMemoryOfVarInSymbolTable(SymbolTable st)
{
    if(st==NULL){
        return -1;
    }
    return st->size;
}