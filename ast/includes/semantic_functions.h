#ifndef __SEMANTIC_FUNCTIONS_H
#define __SEMANTIC_FUNCTIONS_H
void check_type_arithmetic(void *tv);
void free_single_nodes(void *tv);

// 0,1 program ===> otherFunctions mainFunction
void program_rule0(void *tv);

// 1,2 mainFunction ===> TK_MAIN stmts TK_END
void main_rule1(void *tv);
#endif