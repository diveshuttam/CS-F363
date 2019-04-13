#ifndef __TREE_TO_JSON_H
#define __TREE_TO_JSON_H

#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"
#include "ast.h"

void printJSON(Tree t, FILE *fp);
void printParseTreeForHTML(char* testcase_file, char *outfile);
#endif