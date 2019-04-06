#include "semantic_actions.h"

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES]={
    // 0,1 program ===> otherFunctions mainFunction
    {NULL,NULL,&free_single_nodes},
    // 1,2 mainFunction ===> TK_MAIN stmts TK_END
    {NULL,NULL,&free_single_nodes},
    // 2,3 otherFunctions ===> function otherFunctions
    {NULL,NULL,&free_single_nodes},
    // 3,4 otherFunctions ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
    {NULL,NULL,&free_single_nodes},
    // 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&free_single_nodes},
    // 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&free_single_nodes},
    // 7,8 output_par ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 8,9 parameter_list ===> dataType TK_ID remaining_list
    {NULL,NULL,&free_single_nodes},
    // 9,10 dataType ===> primitiveDatatype
    {NULL,NULL,&free_single_nodes},
    // 10,11 dataType ===> constructedDatatype
    {NULL,NULL,&free_single_nodes},
    // 11,12 primitiveDatatype ===> TK_INT
    {NULL,NULL,&free_single_nodes},
    // 12,13 primitiveDatatype ===> TK_REAL
    {NULL,NULL,&free_single_nodes},
    // 13,14 constructedDatatype ===> TK_RECORD TK_RECORDID
    {NULL,NULL,&free_single_nodes},
    // 14,15 remaining_list ===> TK_COMMA parameter_list
    {NULL,NULL,&free_single_nodes},
    // 15,16 remaining_list ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 16,17 stmts ===> typeDefinitions declarations otherStmts returnStmt
    {NULL,NULL,&free_single_nodes},
    // 17,18 typeDefinitions ===> typeDefinition typeDefinitions
    {NULL,NULL,&free_single_nodes},
    // 18,19 typeDefinitions ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM
    {NULL,NULL,&free_single_nodes},
    // fieldDefinitions ===> fieldDefinition fieldDefinition moreFields
    {NULL,NULL,&free_single_nodes},
    // fieldDefinition ===> TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM
    {NULL,NULL,&free_single_nodes},
    // moreFields ===> fieldDefinition moreFields
    {NULL,NULL,&free_single_nodes},
    // moreFields ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // declarations ===> declaration declarations
    {NULL,NULL,&free_single_nodes},
    // declarations ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // declaration ===> TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM
    {NULL,NULL,&free_single_nodes},
    // global_or_not ===> TK_COLON TK_GLOBAL
    {NULL,NULL,&free_single_nodes},
    // global_or_not ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // otherStmts ===> stmt otherStmts
    {NULL,NULL,&free_single_nodes},
    // otherStmts ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // stmt ===> assignmentStmt
    {NULL,NULL,&free_single_nodes},
    // stmt ===> iterativeStmt
    {NULL,NULL,&free_single_nodes},
    // stmt ===> conditionalStmt
    {NULL,NULL,&free_single_nodes},
    // stmt ===> ioStmt
    {NULL,NULL,&free_single_nodes},
    // stmt ===> funCallStmt
    {NULL,NULL,&free_single_nodes},
    // assignmentStmt ===> singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM
    {NULL,NULL,&free_single_nodes},
    // singleOrRecId ===> TK_ID new24
    {NULL,NULL,&free_single_nodes},
    // new24 ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // new24 ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // funCallStmt ===> outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM
    {NULL,NULL,&free_single_nodes},
    // outputParameters ===> TK_SQL idList TK_SQR TK_ASSIGNOP
    {NULL,NULL,&free_single_nodes},
    // outputParameters ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // inputParameters ===> TK_SQL idList TK_SQR
    {NULL,NULL,&free_single_nodes},
    // iterativeStmt ===> TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE
    {NULL,NULL,&free_single_nodes},
    // conditionalStmt ===> TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart
    {NULL,NULL,&free_single_nodes},
    // elsePart ===> TK_ELSE stmt otherStmts TK_ENDIF
    {NULL,NULL,&free_single_nodes},
    // elsePart ===> TK_ENDIF
    {NULL,NULL,&free_single_nodes},
    // ioStmt ===> TK_READ TK_OP singleOrRecId TK_CL TK_SEM
    {NULL,NULL,&free_single_nodes},
    // ioStmt ===> TK_WRITE TK_OP allVar TK_CL TK_SEM
    {NULL,NULL,&free_single_nodes},
    // allVar ===> TK_ID newVar
    {NULL,NULL,&free_single_nodes},
    // allVar ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // allVar ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // newVar ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // newVar ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // arithmeticExpression ===> term expPrime
    {NULL,NULL,&free_single_nodes},
    // expPrime ===> lowPrecedenceOperators term expPrime
    {NULL,NULL,&free_single_nodes},
    // expPrime ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // term ===> factor termPrime
    {NULL,NULL,&free_single_nodes},
    // termPrime ===> highPrecedenceOperators factor termPrime
    {NULL,NULL,&free_single_nodes},
    // termPrime ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // factor ===> TK_OP arithmeticExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // factor ===> all
    {NULL,NULL,&free_single_nodes},
    // highPrecedenceOperators ===> TK_MUL
    {NULL,NULL,&free_single_nodes},
    // highPrecedenceOperators ===> TK_DIV
    {NULL,NULL,&free_single_nodes},
    // lowPrecedenceOperators ===> TK_PLUS
    {NULL,NULL,&free_single_nodes},
    // lowPrecedenceOperators ===> TK_MINUS
    {NULL,NULL,&free_single_nodes},
    // all ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // all ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // all ===> TK_ID temp
    {NULL,NULL,&free_single_nodes},
    // temp ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // temp ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // booleanExpression ===> TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // booleanExpression ===> var relationalOp var
    {NULL,NULL,&free_single_nodes},
    // booleanExpression ===> TK_NOT TK_OP booleanExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // var ===> TK_ID
    {NULL,NULL,&free_single_nodes},
    // var ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // var ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // logicalOp ===> TK_AND
    {NULL,NULL,&free_single_nodes},
    // logicalOp ===> TK_OR
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_LT
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_LE
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_EQ
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_GT
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_GE
    {NULL,NULL,&free_single_nodes},
    // relationalOp ===> TK_NE
    {NULL,NULL,&free_single_nodes},
    // returnStmt ===> TK_RETURN optionalReturn TK_SEM
    {NULL,NULL,&free_single_nodes},
    // optionalReturn ===> TK_SQL idList TK_SQR
    {NULL,NULL,&free_single_nodes},
    // optionalReturn ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // idList ===> TK_ID more_ids
    {NULL,NULL,&free_single_nodes},
    // more_ids ===> TK_COMMA idList
    {NULL,NULL,&free_single_nodes},
    // more_ids ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
};

void assign_semantic_actions(Tree t, grammerRule *gr){
    if(t==NULL)
        return;
    if(t->t.type=='n')
        debug_msg("assigning semantic actions to %s\n", t->t.s.nt->name);
    t->SemanticActions = malloc(sizeof(func_ptr_t)*NO_OF_ATTRIBUTES);
    t->num_rules = NO_OF_ATTRIBUTES;
    for(int j=0;j<NO_OF_ATTRIBUTES&&t!=NULL&&t->t.type=='n';j++){
        t->SemanticActions[j]=semantic_action_map[gr->id][j];
    }
}