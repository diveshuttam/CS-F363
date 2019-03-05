//grammer rules
#ifndef __PARSE_TABLE_H
#define __PARSE_TABLE_H
#define NO_OF_TERMINALS 100
#define NO_OF_NON_TERMINALS 51
#define NO_OF_RULES 92
#define LINE_SIZE 1000
#define FOLLOWS_FILE "parser/rules/follows.txt"
#define FIRSTS_FILE "parser/rules/firsts.txt"
#define GRAMMER_FILE "parser/rules/grammer.txt"
#define NON_TERMINALS_FILE "parser/rules/nonterminals.txt"
#include<stdio.h>
#include<stdlib.h>
#include"lexer.h"
#include"non_terminal_names.h"

typedef struct Terminal
{
    enum token_names StateId;
    char *name;
} Terminal;

typedef struct NonTerminal {
    char *name;
    enum non_terminal_names key;
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
    int isError;
    int id;
} grammerRule;

typedef struct Tree *Tree;

struct Tree
{
    TerminalNonTerminal t;
    int num_child;
    Tree* child;
};

void inorder(const Tree t);
grammerRule** gen_parse_table(const grammerRule *r,const int no_of_rules,const Terminal eps);
Tree parseTree(Stream token_stream,const grammerRule **table,const grammerRule *g);
#endif


