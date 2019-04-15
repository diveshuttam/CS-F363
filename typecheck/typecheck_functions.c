#include "typecheck_functions.h"
#include "ast.h"
#include "symbolTable.h"
#include "st_utils.h"
#include "st_entries.h"
#include "SeqList.h"

void functionTypeCheck(void* tv){
    
}

void typeCheckTerminals(void *tv){
    Tree t = (Tree)tv;
   
    char* typeName;
    StEntry ste = findST(t->tk->val,CurrentSymbolTable);
    if(NULL == ste){
        printf("variable not defined %s\n",t->tk->val);
        return ;
    }
    typeName = ste->et_name;
   
    t->type_name = malloc(sizeof(char)*(strlen(typeName)+1));
    strcpy(t->type_name,typeName);
   
    return ;
}

void tkDotTypeCheck(void* tv){
    Tree t = (Tree)tv;
    Tree* children = t->child;
    char* tkid_typename = children[0]->type_name;
    char* tkfieldIdname = children[1]->tk->val;

    StEntry ste = findST(tkid_typename,GlobalSymbolTable);
    if(ste==NULL){
        printf("ERROR! type %s not declared\n", tkid_typename);
        return;
    }
    record_def_entry rde = (record_def_entry) ste->var_entry;
    SeqList sl = rde->subnodes;
    Element e = find(sl,tkfieldIdname);
    if( e == NULL){
        printf("No such field exists\n");
        return;
    }
    variable_entry ve = (variable_entry) e->d;
    t->type_name =  ve->var_type_name;
    return;
    
}


void binaryOpTypeCheck(void* tv){
    Tree t = (Tree)tv;
    Tree* children = t->child;
    Tree tk_id1,tk_id2;
    tk_id1 = children[0];
    tk_id2 = children[1];
    
    StEntry ste1,ste2;

    ste1=findST(tk_id1->tk->val,CurrentSymbolTable);
    ste2 =findST(tk_id2->tk->val,CurrentSymbolTable);

    char *tk_id1_typename,*tk_id2_typename;
    tk_id1_typename = ste1->et_name;
    tk_id2_typename = ste2->et_name;
    if(strcmp(tk_id1_typename,tk_id2_typename) == 0){
        t->type_name = malloc(sizeof(char)*(strlen(tk_id1_typename)+1));
        strcpy(t->type_name,tk_id1_typename);
    }else{
        printf("Error:arguments have incompatible data types: %s and %s\n",tk_id1_typename,tk_id2_typename);
     
    }
    return;
}

void assignmentStmtTypeCheck(void* tv){
    Tree t = (Tree) tv;
    Tree* children = t->child;
    Tree lhs,rhs;
    lhs = children[0];
    rhs = children[1];
    if(strcmp(lhs->type_name,rhs->type_name) == 0){
        t->type_name = malloc(strlen(lhs->type_name)+1);
        strcpy(t->type_name,lhs->type_name);
    }else{
        printf("Assignment not allowed\n");
    }
    return ;
}