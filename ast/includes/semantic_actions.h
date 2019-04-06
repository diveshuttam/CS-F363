#ifndef __SEMANTIC_ACTIONS_H
#define __SEMANTIC_ACTIONS_H
#include "parserDef.h"
#include "lexerDef.h"
#include "function_ptr.h"
#include "semantic_functions.h"
#define NO_OF_ATTRIBUTES 3

void assign_semantic_actions(Tree t, grammerRule *gr);
#endif