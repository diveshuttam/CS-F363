#include "typecheck.h"
#include "st_entries.h"
#include "typecheck_functions.h"
#include "st_entries.h"
#include "st_utils.h"

static func_ptr_t semantic_action_map_terminals[NO_OF_TERMINALS];
static func_ptr_t semantic_action_map_non_terminals[NO_OF_NON_TERMINALS];

void assign_semantic_functions_map(){
    //terminals
    semantic_action_map_terminals[TK_DOT]=&tkDotTypeCheck;
    semantic_action_map_terminals[TK_PLUS]=&binaryOpTypeCheck;
    semantic_action_map_terminals[TK_MINUS]=&binaryOpTypeCheck;
    semantic_action_map_terminals[TK_MUL]=&binaryOpTypeCheck;
    semantic_action_map_terminals[TK_DIV]=&binaryOpTypeCheck;
    
    semantic_action_map_terminals[TK_ID] = &typeCheckTerminals;
    semantic_action_map_terminals[TK_RNUM] = &typeCheckTerminals;
    semantic_action_map_terminals[TK_NUM] = &typeCheckTerminals;

    //nonterminals
    semantic_action_map_non_terminals[assignmentStmt]=&assignmentStmtTypeCheck;
    semantic_action_map_non_terminals[function] = NULL;
    semantic_action_map_non_terminals[mainFunction] = NULL;
}

Tree post_order_traversal_tc(Tree root, SymbolTable st){
    if(root==NULL)
        return NULL;

    debug_msg("traversing %s\n",root->t.s.nt->name);
    func_ptr_t sa;
    if(root->t.type=='t'){
        sa = semantic_action_map_terminals[root->t.s.t->StateId];
    }
    else{
        sa = semantic_action_map_non_terminals[root->t.s.nt->key];
    }

    if(root->t.type=='n' && (root->t.s.nt->key==function || root->t.s.nt->key==mainFunction)){
        Tree t = root;
        char *funname;
        if(root->t.s.nt->key==function){
            funname = t->child[0]->tk->val;
        }
        else{
            funname=malloc(sizeof(char)*10);
            strcpy(funname,"_main");
        }
        StEntry entry= (StEntry)findST(funname,GlobalSymbolTable);
        if(entry == NULL){
            printf("Function %s not defined\n",funname);
            errors = true;
        }
        function_entry fe=entry->var_entry;
        CurrentSymbolTable = fe->symbol_table;
    }

    for(int i=0; i<(root->num_child);i++){
        if(root->child[i]!=NULL){
            post_order_traversal_tc((root->child)[i], st);
        }
    }
    if(sa!=NULL){
        (sa)(root);
    }
    debug_msg("traversing back %s\n",root->t.s.nt->name);
    return root;
}

void typeCheck(Tree ast,SymbolTable st){
    assign_semantic_functions_map();
    post_order_traversal_tc(ast,st);
}