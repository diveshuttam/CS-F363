#ifndef __SEMANTIC_ACTIONS_H
#define __SEMANTIC_ACTIONS_H
#include "parserDef.h"
#include "lexerDef.h"
#include "function_ptr.h"
#include "semantic_functions.h"
#define NO_OF_ATTRIBUTES 3

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES]={
    // grammer rule 0
    {&check_type_arithmetic},

    // grammer rule 1
    {&check_type_arithmetic,}
};


void assign_semantic_actions(Tree t, grammerRule *gr){
    t->SemanticActions = malloc(sizeof(func_ptr_t)*NO_OF_ATTRIBUTES);
    t->num_rules = NO_OF_ATTRIBUTES;
    for(int j=0;j<NO_OF_ATTRIBUTES;j++){
        t->SemanticActions[j]=semantic_action_map[gr->id][j];
    }
}
#endif