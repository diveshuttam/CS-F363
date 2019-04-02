#include "parserDef.h"
#include "semantic_functions.h"

void check_type_arithmetic(Tree t){
    Tree* child = t->child;
    if(child[0]->type == child[1]->type)
    {
        t->type = child[0]->type;
    }else
    {
        printf("error..");
    }   
}