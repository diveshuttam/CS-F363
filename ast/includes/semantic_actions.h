#ifndef __SEMANTIC_ACTIONS_H
#define __SEMANTIC_ACTIONS_H
#include "parserDef.h"
#include "lexerDef.h"
#include "function_ptr.h"
#include "semantic_functions.h"
#define NO_OF_ATTRIBUTES 3

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES]={
    {&check_type_arithmetic},
};

void assign_semantic_actions(Tree t, grammerRule gr){
    t->SemanticActions = malloc(sizeof(func_ptr_t)*10);
    t->num_rules = NO_OF_ATTRIBUTES;
    for(int i=0;i<NO_OF_RULES;i++)
    {
        for(int j=0;j<NO_OF_ATTRIBUTES;j++){
            t->SemanticActions[j]=semantic_action_map[i][j];
        }
    }
}
#endif