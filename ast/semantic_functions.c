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

// 2,3 otherFunctions ===> function otherFunctions
void otherFunctionsRule2(void* tv){
    Tree otherFunctionsNode = (Tree)tv;
    Tree functionNode = otherFunctionsNode->child[0];
    Tree otherFunctionsNode1 = otherFunctionsNode->child[1];
    int new_num_child ;
    if(otherFunctionsNode1->child == NULL || otherFunctionsNode1->child[0]==NULL){
        new_num_child = 0;
        otherFunctionsNode->child[1] = NULL;
        otherFunctionsNode->num_child--;
        free(otherFunctionsNode1);
    }else{
        new_num_child = otherFunctionsNode1->num_child + 1;
        Tree* new_children = malloc(sizeof(Tree)*new_num_child);
        for(int i=0;i<new_num_child-1;i++){
            new_children[i] = otherFunctionsNode1->child[i];
        }
        new_children[new_num_child - 1] = functionNode;
        free(otherFunctionsNode1);
        free(otherFunctionsNode->child);
        otherFunctionsNode->num_child = new_num_child;
        otherFunctionsNode->child = new_children;
    }
}

// 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
void functionRule4(void* tv){
    Tree functionNode = (Tree)tv;
    Tree tk_funid = functionNode->child[0];
    Tree input_par_node = functionNode->child[1];
    Tree output_par_node = functionNode->child[2];
    Tree tk_sem = functionNode->child[3];
    Tree stmt_node = functionNode->child[4];
    Tree tk_end = functionNode->child[5];
    int output_par_num_child ;
    if(output_par_node->child == NULL || output_par_node->child[0] == NULL){
        output_par_num_child = 0;
    }else{
        output_par_num_child = output_par_node->num_child;
    }

    int new_num_children = 1 + input_par_node->num_child + output_par_num_child + stmt_node->num_child;
    Tree* child = malloc(sizeof(Tree)*new_num_children);
    int i = 0;
    child[i++] = tk_funid;
    int j;
    for(j = 0 ; j < input_par_node->num_child;j++){
        child[i++] = input_par_node->child[j];
    }

    if(output_par_num_child != 0){
        for(j=0 ; j < output_par_node->num_child;j++){
            child[i++] = output_par_node->child[j];
        }
    }

    for(j = 0;j< stmt_node->num_child;j++){
        child[i++] = stmt_node->child[j];
    }

    functionNode->child = child;
    functionNode->num_child = new_num_children;
    free(input_par_node);
    free(output_par_node);
    free(tk_sem);
    free(stmt_node);
    free(tk_end);
    }


// 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
void input_par_Rule5(void* tv){
    Tree input_parNode = (Tree)tv;
    Tree tk_input = input_parNode->child[0];
    Tree tk_parameter = input_parNode->child[1];
    Tree tk_list = input_parNode->child[2];
    Tree tk_sql = input_parNode->child[3];
    Tree parameter_listNode = input_parNode->child[4];
    Tree tk_sqr = input_parNode->child[5];

    input_parNode->child = parameter_listNode->child;
    input_parNode->num_child = parameter_listNode->num_child;

    free(tk_input);
    free(tk_parameter);
    free(tk_list);
    free(tk_sql);
    free(parameter_listNode);
    free(tk_sqr);
}

// 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
void output_par_Rule6(void* tv){
    Tree output_parNode = (Tree)tv;
    Tree tk_output = output_parNode->child[0];
    Tree tk_parameter = output_parNode->child[1];
    Tree tk_list = output_parNode->child[2];
    Tree tk_sql = output_parNode->child[3];
    Tree parameter_listNode = output_parNode->child[4];
    Tree tk_sqr = output_parNode->child[5];

    output_parNode->child = parameter_listNode->child;
    output_parNode->num_child = parameter_listNode->num_child;

    free(tk_output);
    free(tk_parameter);
    free(tk_list);
    free(tk_sql);
    free(parameter_listNode);
    free(tk_sqr);    
}

// 8,9 parameter_list ===> dataType TK_ID remaining_list
void parameter_listRule8(void* tv){
    Tree parameter_listNode = (Tree)tv;
    Tree dataTypeNode = parameter_listNode->child[0];
    Tree tk_id = parameter_listNode->child[1];
    Tree remaining_listNode = parameter_listNode->child[2];
    int remaining_listNode_num_child ;
    if(remaining_listNode->child == NULL || remaining_listNode->child[0] == NULL){
        remaining_listNode_num_child=0;
    }else{
        remaining_listNode_num_child = remaining_listNode->num_child;
    }
    int new_num_children = 1 + 1 + remaining_listNode_num_child;
    Tree* child = malloc(sizeof(Tree)*new_num_children);
    int i=0;
    child[i++] = dataTypeNode->child[0];
    child[i++] = tk_id;
    if(remaining_listNode_num_child != 0 ){
        for(int j=0;j<remaining_listNode_num_child;j++){
            child[i++] = remaining_listNode->child[j];    
        }  
    }

    parameter_listNode->num_child = new_num_children;
    parameter_listNode->child = child;
    free(dataTypeNode);
    free(remaining_listNode);
}

 // 9,10 dataType ===> primitiveDatatype
void dataTypeRule9(void* tv){
    Tree dataTypeNode = (Tree)tv;
    Tree primitiveDatatypeNode = dataTypeNode->child[0];
    dataTypeNode->child = primitiveDatatypeNode->child;
    dataTypeNode->num_child = primitiveDatatypeNode->num_child;
    free(primitiveDatatypeNode);
}