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
