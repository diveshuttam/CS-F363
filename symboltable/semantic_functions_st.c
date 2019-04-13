#include "symbolTable.h"
#include "parserDef.h"
#include "semantic_functions_st.h"

static SymbolTable cST;
static SymbolTable gST;

// 26,27 rule becomes 
// declaration -> type_name id
void ST_declarationRule26(void * tv){
    Tree t=(Tree)tv;
    SymbolTable tb;
    if(t->num_child==2 && t->child[0]->t.type=='t'){
        //local symbol table
        tb = cST;
    }
    if(t->num_child==3 && t->child[0]->t.type=='t' && t->child[2]->tk->state==TK_GLOBAL){
        //global symbol table
        tb = gST;
    }
    enum StEntryType entry_type = VAR_DEC;
    StEntry symboltable_entry = malloc(sizeof(struct StEntry));
    variable_entry v = malloc(sizeof(struct variable_entry));
    symboltable_entry->entry=v;
    symboltable_entry->et=entry_type;

    char *var_name=t->child[1]->tk->val;
    enum token_names var_type = t->child[0]->tk->state;
    char *var_type_name = t->child[0]->tk->val;
    v->var_name=var_name;
    v->var_type=var_type;
    v->var_type_name=var_type_name;
    v->size=-1;
    v->offset=-1;
    switch(var_type){
        //TK_INT
        case TK_INT:
            v->size=2;
            v->offset=getMemoryOfVarInSymbolTable(tb);
            setMemoryOfVarInSymbolTable(tb,v->offset+v->size);
            break;
    
        //TK_REAL
        case TK_REAL:
            v->size=4;
            v->offset=getMemoryOfVarInSymbolTable(tb);
            setMemoryOfVarInSymbolTable(tb,v->offset+v->size);
            break;
        //TK_RECORD
        case TK_RECORDID:
            break;
        default:
            break;
    }

    insertST(var_name,symboltable_entry,tb);
    debug_msg("added entry %s of type %s with offset %d", var_name,  t->child[0]->tk->val, v->offset);
    #ifdef __DEBUG
    getchar();
    #endif
}

// 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_S
// which becomes typeDefinition ===> TK_RECORDID , list of fieldDefinition
void ST_typeDefinitionRule19(void * tv){
    // Tree t=(Tree)tv;
    // enum StType tb;
    // if(t->num_child==3 && t->child[0]->t.type=='t' && t->child[2]->tk->state==TK_GLOBAL){
    //     //local symbol table
    //     tb = CURR_ST;
    // }
    // enum StEntryType entry_type = REC_DEF;
    // StEntry entry = malloc(sizeof(struct StEntry));
    // entry->entry=NULL;
    // entry->et=entry_type;
    // char *var_name=t->child[1]->tk->val;
    // //enum token_names type = t->child[0]->tk->state;
    // insertST(var_name,entry,tb);
    // debug_msg("added entry %s of type %s", var_name,  t->child[0]->tk->val);
    // #ifdef __DEBUG
    // getchar();
    // #endif
}
