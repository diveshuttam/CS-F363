#include "semantic_actions.h"

static func_ptr_t semantic_action_map[NO_OF_RULES][NO_OF_ATTRIBUTES]={
    // 0,1 program ===> otherFunctions mainFunction
    {NULL,NULL,&program_rule0},
    // 1,2 mainFunction ===> TK_MAIN stmts TK_END
    {NULL,NULL,&main_rule1},
    // 2,3 otherFunctions ===> function otherFunctions
    {NULL,NULL,&otherFunctionsRule2},
    // 3,4 otherFunctions ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
    {NULL,NULL,&functionRule4},
    // 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&input_par_Rule5},
    // 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
    {NULL,NULL,&output_par_Rule6},
    // 7,8 output_par ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 8,9 parameter_list ===> dataType TK_ID remaining_list
    {NULL,NULL,&parameter_listRule8},
    // 9,10 dataType ===> primitiveDatatype
    {NULL,NULL,&dataTypeRule9},
    // 10,11 dataType ===> constructedDatatype
    {NULL,NULL,&dataTypeRule10},
    // 11,12 primitiveDatatype ===> TK_INT
    {NULL,NULL,&free_single_nodes},
    // 12,13 primitiveDatatype ===> TK_REAL
    {NULL,NULL,&free_single_nodes},
    // 13,14 constructedDatatype ===> TK_RECORD TK_RECORDID
    {NULL,NULL,&free_single_nodes},
    // 14,15 remaining_list ===> TK_COMMA parameter_list
    {NULL,NULL,&remaining_listRule14},
    // 15,16 remaining_list ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 16,17 stmts ===> typeDefinitions declarations otherStmts returnStmt
    {NULL,NULL,&stmtRule16},
    // 17,18 typeDefinitions ===> typeDefinition typeDefinitions
    {NULL,NULL,&a_gives_b_a_reduce},
    // 18,19 typeDefinitions ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM
    {NULL,NULL,&typeDefinitionRule19},
    // 20,21 fieldDefinitions ===> fieldDefinition fieldDefinition moreFields
    {NULL,NULL,&free_single_nodes},
    // 21,22 fieldDefinition ===> TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 22,23 moreFields ===> fieldDefinition moreFields
    {NULL,NULL,&a_gives_b_a_reduce},
    // 23,24 moreFields ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 24,25 declarations ===> declaration declarations
    {NULL,NULL,a_gives_b_a_reduce},
    // 25,26 declarations ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 26,27 declaration ===> TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 27,28 global_or_not ===> TK_COLON TK_GLOBAL
    {NULL,NULL,&free_single_nodes},
    // 28,29 global_or_not ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 29,30 otherStmts ===> stmt otherStmts
    {NULL,NULL,&a_gives_b_a_reduce_with_both},
    // 30,31 otherStmts ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 31,32 stmt ===> assignmentStmt
    {NULL,NULL,&free_single_nodes},
    // 32,33 stmt ===> iterativeStmt
    {NULL,NULL,&free_single_nodes},
    // 33,34 stmt ===> conditionalStmt
    {NULL,NULL,&free_single_nodes},
    // 34,35 stmt ===> ioStmt
    {NULL,NULL,&free_single_nodes},
    // 35,36 stmt ===> funCallStmt
    {NULL,NULL,&free_single_nodes},
    // 36,37 assignmentStmt ===> singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 37,38 singleOrRecId ===> TK_ID new24
    {NULL,NULL,&singleRule37},
    // 38,39 new24 ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // 39,40 new24 ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 40,41 funCallStmt ===> outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 41,42 outputParameters ===> TK_SQL idList TK_SQR TK_ASSIGNOP
    {NULL,NULL,&free_single_nodes},
    // 42,43 outputParameters ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 43,44 inputParameters ===> TK_SQL idList TK_SQR
    {NULL,NULL,&free_single_nodes},
    // 44,45 iterativeStmt ===> TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE
    {NULL,NULL,&iterativeStmtRule44},
    // 45,46 conditionalStmt ===> TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart
    {NULL,NULL,&free_single_nodes},
    // 46,47 elsePart ===> TK_ELSE stmt otherStmts TK_ENDIF
    {NULL,NULL,&free_single_nodes},
    // 47,48 elsePart ===> TK_ENDIF
    {NULL,NULL,&free_single_nodes},
    // 48,49 ioStmt ===> TK_READ TK_OP singleOrRecId TK_CL TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 49,50 ioStmt ===> TK_WRITE TK_OP allVar TK_CL TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 50,51 allVar ===> TK_ID newVar
    {NULL,NULL,&allVarRule50},
    // 51,52 allVar ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // 52,53 allVar ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // 53,54 newVar ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // 54,55 newVar ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 55,56 arithmeticExpression ===> term expPrime
    {NULL,NULL,&arithmeticExpressionRule55},
    // 56,57 expPrime ===> lowPrecedenceOperators term expPrime
    {NULL,NULL,&expPrimeRule56},
    // 57,58 expPrime ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 58,59 term ===> factor termPrime
    {NULL,NULL,&termRule58},
    // 59,60 termPrime ===> highPrecedenceOperators factor termPrime
    {NULL,NULL,termPrimeRule59},
    // 60,61 termPrime ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 61,62 factor ===> TK_OP arithmeticExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // 62,63 factor ===> all
    {NULL,NULL,&free_single_nodes},
    // 63,64 highPrecedenceOperators ===> TK_MUL
    {NULL,NULL,&free_single_nodes},
    // 64,65 highPrecedenceOperators ===> TK_DIV
    {NULL,NULL,&free_single_nodes},
    // 65,66 lowPrecedenceOperators ===> TK_PLUS
    {NULL,NULL,&free_single_nodes},
    // 66,67 lowPrecedenceOperators ===> TK_MINUS
    {NULL,NULL,&free_single_nodes},
    // 67,68 all ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // 68,69 all ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // 69,70 all ===> TK_ID temp
    {NULL,NULL,&allRule69},
    // 70,71 temp ===> TK_DOT TK_FIELDID
    {NULL,NULL,&free_single_nodes},
    // 71,72 temp ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 72,73 booleanExpression ===> TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // 73,74 booleanExpression ===> var relationalOp var
    {NULL,NULL,&free_single_nodes},
    // 74,75 booleanExpression ===> TK_NOT TK_OP booleanExpression TK_CL
    {NULL,NULL,&free_single_nodes},
    // 75,76 var ===> TK_ID
    {NULL,NULL,&free_single_nodes},
    // 76,77 var ===> TK_NUM
    {NULL,NULL,&free_single_nodes},
    // 77,78 var ===> TK_RNUM
    {NULL,NULL,&free_single_nodes},
    // 78,79 logicalOp ===> TK_AND
    {NULL,NULL,&free_single_nodes},
    // 79,80 logicalOp ===> TK_OR
    {NULL,NULL,&free_single_nodes},
    // 80,81 relationalOp ===> TK_LT
    {NULL,NULL,&free_single_nodes},
    // 81,82 relationalOp ===> TK_LE
    {NULL,NULL,&free_single_nodes},
    // 82,83 relationalOp ===> TK_EQ
    {NULL,NULL,&free_single_nodes},
    // 83,84 relationalOp ===> TK_GT
    {NULL,NULL,&free_single_nodes},
    // 84,85 relationalOp ===> TK_GE
    {NULL,NULL,&free_single_nodes},
    // 85,86 relationalOp ===> TK_NE
    {NULL,NULL,&free_single_nodes},
    // 86,87 returnStmt ===> TK_RETURN optionalReturn TK_SEM
    {NULL,NULL,&free_single_nodes},
    // 87,88 optionalReturn ===> TK_SQL idList TK_SQR
    {NULL,NULL,&free_single_nodes},
    // 88,89 optionalReturn ===> TK_EPS
    {NULL,NULL,&free_single_nodes},
    // 89,90 idList ===> TK_ID more_ids
    {NULL,NULL,a_gives_b_a_reduce},
    // 90,91 more_ids ===> TK_COMMA idList
    {NULL,NULL,free_single_nodes},
    // 91,92 more_ids ===> TK_EPS
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