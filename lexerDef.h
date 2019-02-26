#ifndef LEXERDEF
#define LEXERDEF
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 256
#define MAX_TOKEN_SIZE 40


#define true 1
#define false 0
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
};



typedef struct Token Token;
typedef struct State State;
typedef struct Transition Transition;

struct DFA{
	State* states;
	Transition** transitions;
};
typedef struct DFA DFA;
#endif
