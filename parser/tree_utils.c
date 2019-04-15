//root traversal
#include "parserDef.h"

void visit(const Tree root)
{
    if(root->t.type=='t')
        {
            if(root->tk==NULL){
            printf("error with tree node %s:%d terminal Token points to NULL \n",root->t.s.t->name , root->t.s.t->StateId);
            return;
            }
        printf("%s at line %d:%s\n",root->t.s.t->name,root->tk->line_no,root->tk->val);
    }
    else{ 
        printf("%s %d\n",root->t.s.nt->name, root->t.s.nt->key);
    }
}

void inorder(const Tree root){
    if (root == NULL) 
        return;
    if(root->num_child>0){
        inorder(root->child[0]);
    }
    visit(root);
    for (int i = 1; i < root->num_child; i++) 
    {
        inorder(root->child[i]);
    }
}

int count_nodes(const Tree root){
    int count = 0;
    if (root == NULL) 
        return count;
    if(root->num_child>0){
        for (int i = 0; i < root->num_child; i++) {
            count+=count_nodes(root->child[i]);
        }
    }
    return count+1;
}

size_t get_size_tree_node(const Tree root){
    int count = 0;
    if (root == NULL) 
        return count;
    if(root->num_child>0){
        for (int i = 0; i < root->num_child; i++) {
            count+=get_size_tree_node(root->child[i]);
        }
    }
    return count+sizeof(root);
}