#ifndef _LEXER
#define _LEXER
#include"filenames.h"
#include"lexerDef.h"
#include<stdlib.h>
#include<stdio.h>
#include"twin_buffer.h"
#include"token.h"
#include"populate_dfa.h"
#include"transition.h"
#include"debug.h"
extern bool errors;
#define MAX_TK_LEN 14
//get stream in twin_buffer.h
Token* getNextToken();
void removeComments(const char *testcaseFile,const char *cleanFile);
void removeCommentsStdout(const char *testcaseFile);
void printTokenizedOutput(char* testcase_file);
void removeCommentsStdout(const char *testcaseFile);
void printFileErrorsHighlight(const char *testcaseFile);
#endif