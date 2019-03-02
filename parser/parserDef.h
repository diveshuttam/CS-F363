//grammer rules
#define NO_OF_TERMINALS
#define NO_OF_NON_TERMINALS

#include<stdio.h>
#include<stdlib.h>
typedef struct Terminal
{
    int StateId;
    char *name;
} Terminal;

typedef struct NonTerminal {
    char *name;
    int key;
    Terminal *follows;
    Terminal *first;
} NonTerminal;

typedef union TnT
{
    Terminal t;
    NonTerminal nt;
} TnT;

typedef struct TerminalNonTerminal{
    char type; // terminal:t non-terminal:n
    TnT s;
} TerminalNonTerminal;

typedef struct grammerRule{
    NonTerminal lhs;
    //seqlist of terminals
    TerminalNonTerminal *rhs; 
} grammerRule;

#ifndef __SEQLIST_ELEMENT
#define __SEQLIST_ELEMENT
struct Element{
    int k;
    TerminalNonTerminal t;
};
#endif

#include"SeqList.h"
