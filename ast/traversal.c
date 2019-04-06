
#include "semantic_actions.h"
void post_order_traversal(Tree root){
    if(root==NULL)
        return;
    for(int i=0; i<root->num_child;i++){
        post_order_traversal(root->child[i]);
    }
    for(int i=0;i<root->num_rules;i++){
        if(root->SemanticActions[i]!=NULL)
            (root->SemanticActions[i])(root);
    }
}