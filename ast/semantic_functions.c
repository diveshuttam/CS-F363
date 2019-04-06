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
    if(t->num_child==1){
        Tree temp=t->child[0];
        *t=*t->child[0];
        if(t->child!=NULL)
            t->child[0]=NULL;
        free(temp);
    }
}