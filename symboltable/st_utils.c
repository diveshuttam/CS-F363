#include "symbolTable.h"
#include "st_utils.h"
#include "st_entries.h"
#include "stdio.h"
#include "colors.h"
#include <stdlib.h>

SymbolTable createST(char *st_name){
    SymbolTable st=malloc(sizeof(struct SymbolTable));
    st->ht=newHashTable(MAX_VAR*ALPHA_INV, HASH_A,HASH_B);
    st->sl=newList();
    st->st_name=malloc(strlen(st_name)+1);
    strcpy(st->st_name,st_name);
    st->size=0;
    st->num_entires=0;
    st->parent=NULL;
    return st;
}

void insertST(char *key, StEntry value, SymbolTable st){
    debug_msg("adding entry for %s in symboltable\n",key);
    #ifdef __DEBUG
    getchar();
    #endif
    if(st==NULL)
    {
        return;
    }
    insert(key,value,st->ht);
    Element ele=malloc(sizeof(struct Element));
    ele->d=(void *)value;
    ele->k=(void *)key;
    insertAtEnd(st->sl,ele);
    st->num_entires+=1;
}


void* findST(char *key, SymbolTable st){
    if(st==NULL){
        return NULL;
    }
    void *p=findHT(key,st->ht);
    if(p==NULL && st->parent==NULL){
        return NULL;
    }
    else if(p==NULL){
        return findST(key,st->parent);
    }
    return p;
}

void printRecordTuple(StEntry entry){
    record_def_entry rt = (record_def_entry)entry->var_entry; 
    SeqList sl= rt->subnodes;
    Iterator it=getIterator(sl);
    printf("<");
    while(hasNext(it)){
        Element e=getNext(it);
        variable_entry v=(variable_entry)e->d;
        printf("%s",v->var_type_name);
        it=next(it);
        if(hasNext(it)){
            printf("x");
        }
    }
    printf(">");
}

void printVariableRecDec(StEntry entry){
    variable_entry ve = entry->var_entry;
    printf("%s",ve->var_type_name);
    printf("\t\t\toffset:%d ", ve->offset);
}

void printFunDef(StEntry entry){
    //function_entry fe = entry->var_entry;
    printf("function");
}

void printST(SymbolTable st){
    printf("Printing symboltable for scope: %s\n",st->st_name);
    if(st==NULL || st->num_entires==0){
        printf("Symbol Table is Empty\n");
        return;
    }
    SeqList sl=st->sl;

    Iterator it = getIterator(sl);
    while(hasNext(it)){
        Element e = getNext(it);
        StEntry entry=(StEntry)e->d;
        char *key=e->k;
        if(entry!=NULL){
            printf("%s\t\t name:%s\t size:%d type:",entry->et_name, key, entry->size);
            fflush(stdout);
            if(entry->et==REC_DEF){
                printRecordTuple(entry);
            }
            else if(entry->et==REC_DEC || entry->et==VAR_DEC){
                printVariableRecDec(entry);
            }
            else if(entry->et==FUN_DEF){
                printFunDef(entry);
            }
            printf("\n");
        }
        it=next(it);
    }
}