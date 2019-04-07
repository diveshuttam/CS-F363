#include "parserDef.h"
#include "SeqList.h"
#include "semantic_functions.h"
#include "to_remove.h"

void free_single_nodes(void *tv){
    Tree t=(Tree)tv;
    if(t==NULL){
        return;
    }
    for(int i=0;i<t->num_child;i++){
        Tree c=t->child[i];
        if(c!=NULL&&c->num_child==1){
            if(c->t.type=='n' && c->child[0]!=NULL && c->child[0]->t.type=='t'){
                debug_msg("**assigning %s to %s**\n",c->child[0]->t.s.t->name,t->child[i]->t.s.nt->name);
            }
            else if(c->t.type=='n' && c->child[0]!=NULL && c->child[0]->t.type=='n'){
                debug_msg("**assigning %s to %s**\n",c->child[0]->t.s.nt->name,t->child[i]->t.s.nt->name);
            }
            else if(c->t.type=='n' && c->child[0]==NULL){
                debug_msg("**assigning (null) to %s**\n",t->child[i]->t.s.nt->name);
            }
            t->child[i]=c->child[0];
            free(c);
        }
    }
    if(t->num_child<=1){
        return;
    }
    int curr_count=0;
    debug_msg("ignoring: ");
    for(int i=0;i<t->num_child ;i++){
        
        Tree c=t->child[i];
        if(c==NULL){
            debug_msg("NULL\t")
        }
        else if(((c->t.type=='t'&&c->tk!=NULL&&not_in_ast(c->t.s.t->StateId)))){
            debug_msg("%s\t",c->t.s.t->name);
            free(c);
        }
        else{
            t->child[curr_count]=t->child[i];
            curr_count+=1;
        }
    }
    printf("count %d\n",curr_count);
    t->num_child=curr_count;
}

// 0,1 program ===> otherFunctions mainFunction
void program_rule0(void *tv){
    Tree programNode=(Tree)tv;
    Tree otherFunctionsNode=programNode->child[0];
    Tree mainFunctionNode=programNode->child[1];
    int new_num_child=otherFunctionsNode->num_child+1;
    Tree *new_children=malloc(sizeof(Tree)*new_num_child);
    for(int i=0;i<new_num_child-1;i++){
        new_children[i]=otherFunctionsNode->child[i];
    }
    new_children[new_num_child-1]=mainFunctionNode;
    free(otherFunctionsNode);
    free(programNode->child);
    programNode->num_child=new_num_child;
    programNode->child=new_children;
}

// 1,2 mainFunction ===> TK_MAIN stmts TK_END
void main_rule1(void *tv){
    Tree mainNode=(Tree) tv;
    Tree tkmainNode=mainNode->child[0];
    Tree stmts_node=mainNode->child[1];
    Tree tkendNode=mainNode->child[2];
    int new_no_of_children=stmts_node->num_child;
    mainNode->num_child=new_no_of_children;
    free(tkmainNode);
    free(tkendNode);
    free(mainNode->child);
    mainNode->child=stmts_node->child;
}