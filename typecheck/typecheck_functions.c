#include "typecheck_functions.h"
#include "ast.h"
#include "symbolTable.h"
#include "st_utils.h"

void typeCheckTerminals(void *tv){
    Tree t = (Tree)tv;
    char* typeName = findST(t->tk->val,GlobalSymbolTable);
    t->type_name = malloc(sizeof(char)*(strlen(typeName)+1));
    strcpy(t->type_name,typeName);
    return ;
}

void tkDotTypeCheck(void* tv){
    Tree t = (Tree)tv;
    Tree* children = t->child;
    Tree tk_fieldId = children[0];
    char* fieldTypeName = findST(tk_fieldId->tk->val,GlobalSymbolTable);
    t->type_name = malloc(sizeof(char)*(strlen(fieldTypeName) +1));
    strcpy(t->type_name,fieldTypeName);
    return ; 
}


void binaryOpTypeCheck(void* tv){
    Tree t = (Tree)tv;
    Tree* children = t->child;
    Tree tk_id1,tk_id2;
    tk_id1 = children[0];
    tk_id2 = children[1];
    
    char* tk_id1_typeName =findST(tk_id1->tk->val,GlobalSymbolTable);
    char* tk_id2_typeName =findST(tk_id2->tk->val,GlobalSymbolTable);

    if(strcmp(tk_id1_typeName,tk_id2_typeName) == 0){
        t->type_name = malloc(sizeof(char)*(strlen(tk_id1_typeName)+1));
        strcpy(t->type_name,tk_id1_typeName);
    }else{
        printf("Error:arguments have incompatible data types: %s and %s\n",tk_id1_typeName,tk_id2_typeName);
     
    }
    return;
}

