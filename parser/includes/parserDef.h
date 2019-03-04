//grammer rules
#define NO_OF_TERMINALS 100
#define NO_OF_NON_TERMINALS 51
#define NO_OF_RULES 100
#define LINE_SIZE 1000
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
    int follows_size;
    Terminal *firsts;
    int firsts_size;
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
    int num_of_rhs;
} grammerRule;


