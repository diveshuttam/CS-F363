#ifndef _TOKEN
#define _TOKEN
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"

#define TYPES_OF_TOKEN 100
#define TK_NAME_SIZE 30
#define ALPHA_INV 1.33
#define HASH_A 5
#define HASH_B 5183
#define TOKEN_SIZE 30
#define MAX_RHS 20
#define MAX_CSV_TOKEN_LEN 100
#define MAX_LINE_LEN 150
#define MAX_STATES 56
#define CHAR_LEN 128
#define NUM_KEYWORDS 20
#define MAX_FF 22

#include "hash.h"
#include "token_names.h"

char ** get_token_names();
void destroy_token_name_table(char **arr);
hashTable get_token_hasht();
hashTable get_keyword_hasht();
#endif