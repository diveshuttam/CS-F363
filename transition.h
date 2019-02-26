#ifndef TRANSITION
#define TRANSITION
#include "lexerDef.h"
Token get_next_token(Transition** transition_table,State *states,char* buffer,int buffersize,int* start);
#endif
