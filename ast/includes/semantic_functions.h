#ifndef __SEMANTIC_FUNCTIONS_H
#define __SEMANTIC_FUNCTIONS_H
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
void typeDefinitionsRule17(void* tv);
#endif