#ifndef __SEMANTIC_FUNCTIONS_AST_H
#define __SEMANTIC_FUNCTIONS_AST_H
void check_type_arithmetic(void *tv);
void free_single_nodes(void *tv);

// 0,1 program ===> otherFunctions mainFunction
void program_rule0(void *tv);

// 1,2 mainFunction ===> TK_MAIN stmts TK_END
void main_rule1(void *tv);

// 2,3 otherFunctions ===> function otherFunctions
void otherFunctionsRule2(void* tv);

// 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
void functionRule4(void* tv);

// 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
void input_par_Rule5(void* tv);

// 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
void output_par_Rule6(void* tv);

// 8,9 parameter_list ===> dataType TK_ID remaining_list
void parameter_listRule8(void* tv);

// 9,10 dataType ===> primitiveDatatype
void dataTypeRule9(void* tv);

// 10,11 dataType ===> constructedDatatype
void dataTypeRule10(void *tv);


// 14,15 remaining_list ===> TK_COMMA parameter_list
void remaining_listRule14(void* tv);

// 16,17 stmts ===> typeDefinitions declarations otherStmts returnStmt
void stmtRule16(void* tv);

// 17,18 typeDefinitions ===> typeDefinition typeDefinitions
// void typeDefinitionsRule17(void* tv);

// 22,23 moreFields ===> fieldDefinition moreFields
// 24,25 declarations ===> declaration declarations
void a_gives_b_a_reduce(void* tv);

void a_gives_b_a_reduce_with_both(void *tv);

// 55,56 arithmeticExpression ===> term expPrime
void arithmeticExpressionRule55(void *tv);

// 44,45 iterativeStmt ===> TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE
void iterativeStmtRule44(void *tv);

// 69,70 all ===> TK_ID temp
void allRule69(void *tv);

// 58,59 term ===> factor termPrime
void termRule58(void *tv);

// 59,60 termPrime ===> highPrecedenceOperators factor termPrime
void termPrimeRule59(void *tv);

// 37,38 singleOrRecId ===> TK_ID new24
void singleRule37(void *tv);

// 50,51 allVar ===> TK_ID newVar
void allVarRule50(void *tv);

// 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM
void typeDefinitionRule19(void *tv);

// 56,57 expPrime ===> lowPrecedenceOperators term expPrime
void expPrimeRule56(void *tv);

// 36,37 assignmentStmt ===> singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM
void assignmentStmtRule36(void *tv);
#endif