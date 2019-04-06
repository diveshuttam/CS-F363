
#include "semantic_actions.h"
void post_order_traversal(Tree root){
    if(root==NULL || root->t.type=='t')
        return;
    debug_msg("traversing %s\n",root->t.s.nt->name);
    for(int i=0; i<(root->num_child);i++){
        if(root->child!=NULL)
            post_order_traversal((root->child)[i]);
    }
    for(int i=0;i<NO_OF_ATTRIBUTES;i++){
        if((root->SemanticActions)[i]!=NULL)
            ((root->SemanticActions)[i])(root);
    }
}