#ifndef _TOKEN
#define _TOKEN
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TYPES_OF_TOKEN 100
#define TK_NAME_SIZE 20

#include<token_names.h>


char ** get_token_names();
void destroy_token_name_table(char **arr);
#endif