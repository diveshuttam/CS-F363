#ifndef __AST_H
#define __AST_H
#include "parserDef.h"
Tree convert_parse_to_ast(Tree t);  //inplace conversion
Tree getASTFromFile(char *testcasefile);
void printASTOutput(char *testcasefile);
void printRatioParseAndAST(char *testcasefile);
#endif