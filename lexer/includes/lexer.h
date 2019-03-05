#ifndef _LEXER
#define _LEXER
#include"lexerDef.h"
#include<stdlib.h>
#include<stdio.h>
#include"twin_buffer.h"
#include"token.h"
#include"populate_dfa.h"
#include"transition.h"

#define DFA_RULES_FILE "./lexer/dfa_states.ccsv"

//get stream in twin_buffer.h
Token getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);
#endif