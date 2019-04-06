#include "parserDef.h"
#include "SeqList.h"
#include "semantic_functions.h"


void free_single_nodes(void *tv){
    Tree t=(Tree)tv;
    if(t->num_child==1){
        Tree temp=t->child[0];
        *t=*t->child[0];
        free(temp);
    }
}