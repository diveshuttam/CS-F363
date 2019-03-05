#ifndef _TRANSITION
#define _TRANSITION
#include "lexerDef.h"
#define MAX_TOKEN_NUMS 200
Token get_next_token_sub(Stream s,const Transition** transition_table,const State *states);
#endif
