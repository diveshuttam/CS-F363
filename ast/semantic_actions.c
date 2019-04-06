#include "semantic_actions.h"

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES];

void assign_semantic_actions_map()
{
    static bool already_assigned=false;
    if(already_assigned==false){
        for(int i=0;i<NO_OF_RULES;i++){
            semantic_action_map[i][0]=&free_single_nodes;
            semantic_action_map[i][1]=NULL;
            semantic_action_map[i][2]=NULL;
        }
    }
}
void assign_semantic_actions(Tree t, grammerRule *gr){
    assign_semantic_actions_map();
    //func_ptr_t** semantic_action_map=get_semantic_action_map();
    t->SemanticActions = malloc(sizeof(func_ptr_t)*NO_OF_ATTRIBUTES);
    t->num_rules = NO_OF_ATTRIBUTES;
    for(int j=0;j<NO_OF_ATTRIBUTES;j++){
        t->SemanticActions[j]=semantic_action_map[gr->id][j];
    }
}