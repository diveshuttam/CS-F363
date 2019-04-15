#ifndef __ST_ENTRIES_H
#define __ST_ENTRIES_H
#include "token_names.h"
typedef struct record_def_entry{
    int size;
    SeqList subnodes;
} *record_def_entry;

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
    SeqList input_par;
    SeqList output_par;
}*function_entry;

#endif