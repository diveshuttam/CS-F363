#include<stdio.h>
#define MAX_SIZE 256
#define token_size 40
struct State{
	int is_final_state;
	int is_retracting_state;
	int next_state;
	int current_state;
};
struct Token{
	char* token_type;
	int state;
};
typedef struct Token Token;
typedef struct State State;
