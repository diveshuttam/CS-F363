#ifndef __SEMANTIC_FUNCTIONS_ST
#define __SEMANTIC_FUNCTIONS_ST
#include "st_entries.h"
// 26,27 rule becomes 
// declaration -> type_name id
void ST_declarationRule26(void *);

// 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_S
// which becomes typeDefinition ===> TK_RECORDID , list of fieldDefinition
void ST_typeDefinitionRule19(void *);

#endif