#include "parserDef.h"
#include "SeqList.h"
#include "semantic_functions.h"

void check_type_arithmetic(void* tv){
    Tree t=(Tree)(tv);
    Tree* child = t->child;
    if(child[0]->type == child[1]->type)
    {
        t->type = child[0]->type;
    }else
    {
        printf("error..");
    }
}

void free_single_nodes(void *tv){
    Tree t=(Tree)tv;
    if(t==NULL){
        return;
    }
    for(int i=0;i<t->num_child;i++){
        Tree c=t->child[i];
        if(c!=NULL&&c->num_child==1){
            t->child[i]=c->child[0];
            free(c);
        }
    }
}