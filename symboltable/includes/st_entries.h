#ifndef __ST_ENTRIES_H
#define __ST_ENTRIES_H
#include "token_names.h"
typedef struct variable_entry{
    char *var_name;
    int offset;
    int size;
    enum token_names var_type;
    char *var_type_name;
} *variable_entry;

typedef struct function_entry{
    int base;
    int size;
    void *symbol_table;
}*function_entry;

#endif