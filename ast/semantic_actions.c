#include "semantic_actions.h"

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES]={
    // 0,1 program ===> otherFunctions mainFunction
    {NULL,NULL,&program_rule0},
    // 1,2 mainFunction ===> TK_MAIN stmts TK_END
    {NULL,NULL,&main_rule1},
    // 2,3 otherFunctions ===> function otherFunctions
    {NULL,NULL,&otherFunctionsRule2},
    // 3,4 otherFunctions ===> TK_EPS
    {NULL,NULL,NULL},
    // 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
    {NULL,NULL,&functionRule4},
    // 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&input_par_Rule5},
    // 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&output_par_Rule6},
    // 7,8 output_par ===> TK_EPS
    {NULL,NULL,NULL},
    // 8,9 parameter_list ===> dataType TK_ID remaining_list
    {NULL,NULL,&parameter_listRule8},
    // 9,10 dataType ===> primitiveDatatype
    {NULL,NULL,&dataTypeRule9},
    // 10,11 dataType ===> constructedDatatype
    {NULL,NULL,&dataTypeRule10},
    // 11,12 primitiveDatatype ===> TK_INT
    {NULL,NULL,NULL},
    // 12,13 primitiveDatatype ===> TK_REAL
    {NULL,NULL,NULL},
    // 13,14 constructedDatatype ===> TK_RECORD TK_RECORDID
    {NULL,NULL,NULL},
    // 14,15 remaining_list ===> TK_COMMA parameter_list
    {NULL,NULL,&remaining_listRule14},
    // 15,16 remaining_list ===> TK_EPS
    {NULL,NULL,NULL},
    // 16,17 stmts ===> typeDefinitions declarations otherStmts returnStmt
    {NULL,NULL,NULL},
    // 17,18 typeDefinitions ===> typeDefinition typeDefinitions
    {NULL,NULL,&typeDefinitionsRule17},
    // 18,19 typeDefinitions ===> TK_EPS
    {NULL,NULL,NULL},
    // 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM
    {NULL,NULL,NULL},
    // fieldDefinitions ===> fieldDefinition fieldDefinition moreFields
    {NULL,NULL,NULL},
    // fieldDefinition ===> TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM
    {NULL,NULL,NULL},
    // moreFields ===> fieldDefinition moreFields
    {NULL,NULL,NULL},
    // moreFields ===> TK_EPS
    {NULL,NULL,NULL},
    // declarations ===> declaration declarations
    {NULL,NULL,NULL},
    // declarations ===> TK_EPS
    {NULL,NULL,NULL},
    // declaration ===> TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM
    {NULL,NULL,NULL},
    // global_or_not ===> TK_COLON TK_GLOBAL
    {NULL,NULL,NULL},
    // global_or_not ===> TK_EPS
    {NULL,NULL,NULL},
    // otherStmts ===> stmt otherStmts
    {NULL,NULL,NULL},
    // otherStmts ===> TK_EPS
    {NULL,NULL,NULL},
    // stmt ===> assignmentStmt
    {NULL,NULL,NULL},
    // stmt ===> iterativeStmt
    {NULL,NULL,NULL},
    // stmt ===> conditionalStmt
    {NULL,NULL,NULL},
    // stmt ===> ioStmt
    {NULL,NULL,NULL},
    // stmt ===> funCallStmt
    {NULL,NULL,NULL},
    // assignmentStmt ===> singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM
    {NULL,NULL,NULL},
    // singleOrRecId ===> TK_ID new24
    {NULL,NULL,NULL},
    // new24 ===> TK_DOT TK_FIELDID
    {NULL,NULL,NULL},
    // new24 ===> TK_EPS
    {NULL,NULL,NULL},
    // funCallStmt ===> outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM
    {NULL,NULL,NULL},
    // outputParameters ===> TK_SQL idList TK_SQR TK_ASSIGNOP
    {NULL,NULL,NULL},
    // outputParameters ===> TK_EPS
    {NULL,NULL,NULL},
    // inputParameters ===> TK_SQL idList TK_SQR
    {NULL,NULL,NULL},
    // iterativeStmt ===> TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE
    {NULL,NULL,NULL},
    // conditionalStmt ===> TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart
    {NULL,NULL,NULL},
    // elsePart ===> TK_ELSE stmt otherStmts TK_ENDIF
    {NULL,NULL,NULL},
    // elsePart ===> TK_ENDIF
    {NULL,NULL,NULL},
    // ioStmt ===> TK_READ TK_OP singleOrRecId TK_CL TK_SEM
    {NULL,NULL,NULL},
    // ioStmt ===> TK_WRITE TK_OP allVar TK_CL TK_SEM
    {NULL,NULL,NULL},
    // allVar ===> TK_ID newVar
    {NULL,NULL,NULL},
    // allVar ===> TK_NUM
    {NULL,NULL,NULL},
    // allVar ===> TK_RNUM
    {NULL,NULL,NULL},
    // newVar ===> TK_DOT TK_FIELDID
    {NULL,NULL,NULL},
    // newVar ===> TK_EPS
    {NULL,NULL,NULL},
    // arithmeticExpression ===> term expPrime
    {NULL,NULL,NULL},
    // expPrime ===> lowPrecedenceOperators term expPrime
    {NULL,NULL,NULL},
    // expPrime ===> TK_EPS
    {NULL,NULL,NULL},
    // term ===> factor termPrime
    {NULL,NULL,NULL},
    // termPrime ===> highPrecedenceOperators factor termPrime
    {NULL,NULL,NULL},
    // termPrime ===> TK_EPS
    {NULL,NULL,NULL},
    // factor ===> TK_OP arithmeticExpression TK_CL
    {NULL,NULL,NULL},
    // factor ===> all
    {NULL,NULL,NULL},
    // highPrecedenceOperators ===> TK_MUL
    {NULL,NULL,NULL},
    // highPrecedenceOperators ===> TK_DIV
    {NULL,NULL,NULL},
    // lowPrecedenceOperators ===> TK_PLUS
    {NULL,NULL,NULL},
    // lowPrecedenceOperators ===> TK_MINUS
    {NULL,NULL,NULL},
    // all ===> TK_NUM
    {NULL,NULL,NULL},
    // all ===> TK_RNUM
    {NULL,NULL,NULL},
    // all ===> TK_ID temp
    {NULL,NULL,NULL},
    // temp ===> TK_DOT TK_FIELDID
    {NULL,NULL,NULL},
    // temp ===> TK_EPS
    {NULL,NULL,NULL},
    // booleanExpression ===> TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL
    {NULL,NULL,NULL},
    // booleanExpression ===> var relationalOp var
    {NULL,NULL,NULL},
    // booleanExpression ===> TK_NOT TK_OP booleanExpression TK_CL
    {NULL,NULL,NULL},
    // var ===> TK_ID
    {NULL,NULL,NULL},
    // var ===> TK_NUM
    {NULL,NULL,NULL},
    // var ===> TK_RNUM
    {NULL,NULL,NULL},
    // logicalOp ===> TK_AND
    {NULL,NULL,NULL},
    // logicalOp ===> TK_OR
    {NULL,NULL,NULL},
    // relationalOp ===> TK_LT
    {NULL,NULL,NULL},
    // relationalOp ===> TK_LE
    {NULL,NULL,NULL},
    // relationalOp ===> TK_EQ
    {NULL,NULL,NULL},
    // relationalOp ===> TK_GT
    {NULL,NULL,NULL},
    // relationalOp ===> TK_GE
    {NULL,NULL,NULL},
    // relationalOp ===> TK_NE
    {NULL,NULL,NULL},
    // returnStmt ===> TK_RETURN optionalReturn TK_SEM
    {NULL,NULL,NULL},
    // optionalReturn ===> TK_SQL idList TK_SQR
    {NULL,NULL,NULL},
    // optionalReturn ===> TK_EPS
    {NULL,NULL,NULL},
    // idList ===> TK_ID more_ids
    {NULL,NULL,NULL},
    // more_ids ===> TK_COMMA idList
    {NULL,NULL,NULL},
    // more_ids ===> TK_EPS
    {NULL,NULL,NULL},
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