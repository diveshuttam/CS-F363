#include "ast.h"
#include "code_gen.h"
#include "code_gen_semantic.h"
#include "symbolTable.h"
#include "colors.h"
#include "st_entries.h"
#include "st_utils.h"

static func_ptr_t semantic_action_map_terminals[NO_OF_TERMINALS];
static func_ptr_t semantic_action_map_non_terminals[NO_OF_NON_TERMINALS];

void assign_semantic_functions_map_cg(){
    //terminals
    semantic_action_map_terminals[TK_PLUS]=&operation_cg;
    semantic_action_map_terminals[TK_MINUS]=&operation_cg;
    semantic_action_map_terminals[TK_MUL]=&operation_cg;
    semantic_action_map_terminals[TK_DIV]=&operation_cg;
    

    //nonterminals
    semantic_action_map_non_terminals[assignmentStmt]=&assignmentStmt_cg;
    semantic_action_map_non_terminals[program] = &functions_cg;
    //semantic_action_map_non_terminals[mainFunction] = &functions_cg;
}

Tree post_order_traversal_cg(Tree root, SymbolTable st){
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
        char *key;
        if(root->t.s.nt->key==mainFunction){
            key=malloc(sizeof(char)*10);
            strcpy(key,"_main");
        }
        else{
            key = root->child[0]->tk->val;
        }
        StEntry entry= (StEntry)findST(key,GlobalSymbolTable);
        function_entry fe=entry->var_entry;
        CurrentSymbolTable = fe->symbol_table;
    }

    for(int i=0; i<(root->num_child);i++){
        if(root->child!=NULL){
            post_order_traversal_cg((root->child)[i], st);
        }
    }
    if(sa!=NULL){
        (sa)(root);
    }
    debug_msg("traversing back %s\n",root->t.s.nt->name);
    return root;
}

void genCodegen(Tree ast,SymbolTable st){
    assign_semantic_functions_map_cg();
    post_order_traversal_cg(ast,st);
}

void printCodegenFromFile(char *file, char *asmfile){
    errors=false;
    Tree ast = getASTFromFile(file);
    SymbolTable st=genSymbolTable(ast);
    GlobalSymbolTable = st;
    FILE *fp = fopen(asmfile,"w");
    if(errors==false){
        printf(ANSI_COLOR_GREEN "Compilation Successful!\n" ANSI_COLOR_RESET);
        genCodegen(ast,st);
        if(ast->code==NULL){
            printf(ANSI_COLOR_RED "Internal Error in CODEGEN" ANSI_COLOR_RESET);
        }
        fprintf(fp,"%s",ast->code);
    }
    else{
        printf(ANSI_COLOR_RED "ERRORS while compiling. Aborting\n" ANSI_COLOR_RESET);
        return;
    }
    fflush(stdout);
}