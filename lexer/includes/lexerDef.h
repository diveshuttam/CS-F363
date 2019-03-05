#ifndef _LEXERDEF
#define _LEXERDEF
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash.h"
#define MAX_SIZE 256
#define MAX_TOKEN_SIZE 150
#define BLOCK_SIZE 4096

#include<stdbool.h>
#include"twin_buffer.h"

struct State{
	int val;
	int is_final_state;
	int is_retracting_state;
};

struct Transition{
	int next_state;
	int current_state;
	char character;
};

struct Token{
	char* val;
	int state;
	int len;
	int line_no;
};

typedef struct Token Token;
typedef struct State State;
typedef struct Transition Transition;

struct DFA{
	State* states;
	Transition** transitions;
	char ** token_names;
	hashTable token_ht;
};
typedef struct DFA DFA;
#endif
