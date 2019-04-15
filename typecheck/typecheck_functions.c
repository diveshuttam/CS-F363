#include "typecheck_functions.h"
#include "ast.h"
#include "symbolTable.h"
#include "st_utils.h"
#include "st_entries.h"
#include "SeqList.h"


//check if return values are ok
// void functionTypeCheck(void* tv){
//     Tree t = (Tree)tv;
//     char* funcName = t->child[0]->tk->val;
//     function_entry fe = findST(funcName,CurrentSymbolTable);
//     // SeqList inputPar = fe->input_par;
//     SeqList outputPar = fe->output_par;
//     Tree rtStnmt = t->child[t->num_child-1];
//     Tree* rtStnmtValues = rtStnmt->child; 
//     int i=0;
//     Iterator it = getIterator(outputPar);
//     while (hasNext(it))
//     {
//         Element e = getNext(it);
//         StEntry se=(StEntry)e->d;
//         variable_entry ve = se->var_entry;
//         if(strcmp(rtStnmtValues[i]->type_name,ve->var_type_name) != 0){
//             printf("Return parameter differ in output type %s and %s on line %d\n",rtStnmtValues[i]->type_name,ve->var_type_name,rtStnmt->tk->line_no);    
//             return;
//         }
//         it = next(it);
//         i++;
//     }
//     if(i != rtStnmt->num_child){
//         printf("Expected to return %d values returns %d values\n",i,rtStnmt->tk->line_no);
//         return;
//     }
// }

void typeCheckTerminals(void *tv){
    Tree t = (Tree)tv;
   
    char* typeName;
    if(t->tk->state==TK_RNUM){
        t->type_name=malloc(strlen("real")+1);
        strcpy(t->type_name,"real");
        return;
    }
    else if(t->tk->state==TK_NUM){
        t->type_name=malloc(strlen("int")+1);
        strcpy(t->type_name,"int");
        return;
    }
    StEntry ste = findST(t->tk->val,CurrentSymbolTable);
    if(NULL == ste){
        printf("variable not defined %s\n",t->tk->val);
        errors = true;
        return ;
    }
    variable_entry ve = ste->var_entry;
    typeName = ve->var_type_name;
   
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
        errors = true;
        return;
    }
    record_def_entry rde = (record_def_entry) ste->var_entry;
    SeqList sl = rde->subnodes;
    Element e = find(sl,tkfieldIdname);
    if( e == NULL){
        printf("No such field exists\n");
        errors = true;
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
    if(NULL == ste1 || NULL == ste2) return ;
    char *tk_id1_typename,*tk_id2_typename;
    variable_entry v1=(variable_entry)(ste1->var_entry);
    variable_entry v2=(variable_entry)(ste2->var_entry);
    tk_id1_typename = v1->var_type_name;
    tk_id2_typename = v2->var_type_name;
    if(strcmp(tk_id1_typename,tk_id2_typename) == 0){
        t->type_name = malloc(sizeof(char)*(strlen(tk_id1_typename)+1));
        strcpy(t->type_name,tk_id1_typename);
    }else{
        printf("Error:arguments have incompatible data types: %s and %s on line %d\n",tk_id1_typename,tk_id2_typename,tk_id1->tk->line_no);
        errors = true;
    }
    return;
}

void assignmentStmtTypeCheck(void* tv){
    Tree t = (Tree) tv;
    Tree* children = t->child;
    Tree lhs,rhs;
    lhs = children[0];
    rhs = children[1];
    if(lhs->type_name!=NULL && rhs->type_name!=NULL && strcmp(lhs->type_name,rhs->type_name) == 0){
        t->type_name = malloc(strlen(lhs->type_name)+1);
        strcpy(t->type_name,lhs->type_name);
    }else{
        printf("Assignment not allowed for %s and %s on line %d \n",lhs->type_name,rhs->type_name,lhs->tk->line_no);
        errors = true;
    }
    return ;
}