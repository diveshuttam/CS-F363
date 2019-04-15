//grammer rules
#ifndef __PARSER_DEF_H
#define __PARSER_DEF_H
#define NO_OF_TERMINALS 100
#define NO_OF_NON_TERMINALS 51
#define NO_OF_RULES 92
#define LINE_SIZE 1000
#include "filenames.h"
#include<stdio.h>
#include<stdlib.h>
#include"lexer.h"
#include"non_terminal_names.h"
#include"debug.h"
#include"function_ptr.h"

typedef struct Terminal
{
    enum token_names StateId;
    char *name;
} Terminal;

typedef struct NonTerminal {
    char *name;
    enum non_terminal_names key;
    Terminal **follows;
    int follows_size;
    Terminal **firsts;
    int firsts_size;
} NonTerminal;

typedef union TnT
{
    Terminal *t;
    NonTerminal *nt;
} TnT;

typedef struct TerminalNonTerminal{
    char type; // terminal:t non-terminal:n
    TnT s;
} TerminalNonTerminal;

typedef struct grammerRule{
    NonTerminal *lhs;
    //seqlist of terminals
    TerminalNonTerminal **rhs; 
    int num_of_rhs;
    int isError;
    int isSyn;
    int id;
    int part_of_first;
    int can_be_eps; //to differentiate between syn set of first and follows
} grammerRule;

typedef struct Tree *Tree;

struct Tree
{
    TerminalNonTerminal t;
    int num_child;
    int gr_no;
    Tree* child;
    Token *tk;
    #include "derived_attributes.xfile"
};

grammerRule** gen_parse_table(const grammerRule *r,const int no_of_rules,const Terminal* eps);
Tree parseTree(Stream token_stream,const grammerRule **table,const grammerRule *g,const grammerRule *start_rule, const Terminal *bottom_symbol);
Tree getParsedTreeFromFile(char *filename);
void printParsedOutput(char *filename);
#endif


