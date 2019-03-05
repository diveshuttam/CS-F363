#ifndef _TRANSITION
#define _TRANSITION
#include "lexerDef.h"
#define MAX_TOKEN_NUMS 200
Token get_next_token_sub(Stream s, Transition** transition_table,State *states);
#endif
