#include "st_utils.h"
#include "symbolTable.h"
#include "ast.h"
#include "st_entries.h"
#include "colors.h"
#include "typecheck.h"
SymbolTable GlobalSymbolTable=NULL;
SymbolTable CurrentSymbolTable=NULL;
void updateRecordEntires(Tree ast, SymbolTable st);
void updateGlobalVariables(Tree ast, SymbolTable st);
void updateOtherVariables(Tree ast, SymbolTable st);

SymbolTable genSymbolTable(Tree ast){
    SymbolTable gST=createST("global");
    
    //record entires first
    updateRecordEntires(ast,gST);
    
    //global variables next and functions next
    updateGlobalVariables(ast,gST);
    int offset=0;
    char *key=NULL;
    function_entry fe=NULL;
    for(int i=0;i<ast->num_child;i++){
        offset=gST->size;
        if(ast->child[i]->t.s.nt->key==mainFunction){
            key=malloc(sizeof(char)*10);
            strcpy(key,"_main");
        }
        else{
            key = ast->child[i]->child[0]->tk->val;
        }
        //other variables last (local, parameters)
        
        SymbolTable cST = createST(key);
        cST->parent=gST;
        updateOtherVariables(ast->child[i],cST);
        StEntry ent = malloc(sizeof(struct StEntry));
        ent->et=FUN_DEF;
        ent->et_name=malloc(sizeof("FUN_DEF")+1);
        strcpy(ent->et_name,"FUN_DEF");
        ent->size=cST->size;
        ent->var_entry=NULL;

        fe = malloc(sizeof(struct function_entry));
        fe->size=cST->size;
        fe->symbol_table=cST;
        fe->base=offset;
        ent->var_entry=fe;
        gST->size+=fe->size;
        insertST(key,ent, gST);
    }
    return gST;
}

void updateRecordEntires(Tree ast, SymbolTable st){
    if(ast==NULL || st==NULL){
        return;
    }
    else if(ast->t.type=='n' && ast->t.s.nt->key==typeDefinition){
        if(!(ast->child[0]->t.type=='t' && ast->child[0]->t.s.t->StateId==TK_RECORDID)){
            printf("ERROR\n");
            return;
        }
        
        char *key=ast->child[0]->tk->val;
        // if(findST(key,st)!=NULL){
        //     printf("Error! Type name %s redefined at line %d\n", key, ast->child[0]->tk->line_no);
        // }
        StEntry et=malloc(sizeof(struct StEntry));
        et->et_name=malloc(strlen("REC_DEF")+1);
        strcpy(et->et_name,"REC_DEF");
        record_def_entry re=malloc(sizeof(struct record_def_entry));
        et->et=REC_DEF;
        et->var_entry=re;
        et->size=0;
        re->size=0;
        SeqList sl=newList();
        // Iterator it = getIterator(sl);
        re->subnodes=sl;
        Element E=NULL;
        int coffset=0;
        for(int i=1;i<ast->num_child;i++){
            E=malloc(sizeof(struct Element));
            variable_entry var_entry=malloc(sizeof(struct variable_entry));
            E->k=(Key)(ast->child[i]->child[1]->t.s.t->name);
            // if(find(sl,ast->child[i]->child[1]->t.s.t->name)!=NULL){
            //     printf("Error! variable %s redefined at line %d\n", key, ast->child[0]->tk->line_no);
            //     continue;
            // }
            E->d=(Data)(var_entry);
            var_entry->var_type=ast->child[i]->child[0]->t.s.t->StateId;
            int sz=0;
            if(var_entry->var_type==TK_INT){
                sz=INT_SIZE;
            }
            if(var_entry->var_type==TK_REAL){
                sz=REAL_SIZE;
            }
            var_entry->size=sz;
            var_entry->var_name=ast->child[i]->child[1]->tk->val;
            var_entry->offset=coffset;
            var_entry->var_type_name=ast->child[i]->child[0]->t.s.t->name;
            coffset+=sz;
            re->size+=sz;
            et->size+=sz;
            insertAtEnd(sl,E);
        }
        insertST(key,et,st);
        return;
    }
    for(int i=0;i<ast->num_child;i++){
        updateRecordEntires(ast->child[i],st);
    }
}


void updateGlobalVariables(Tree ast,SymbolTable st){
    int offset=st->size;
    if(ast==NULL || st==NULL){
        return;
    }
    else if(ast->t.type=='n' && ast->t.s.nt->key==declaration && ast->num_child==3 && ast->child[2]->t.s.t->StateId==TK_GLOBAL){
        if(!(ast->child[0]->t.type=='t')){
            printf("ERROR\n");
            return;
        }
        char *key=ast->child[1]->tk->val;
        StEntry et=malloc(sizeof(struct StEntry));
        variable_entry ve=malloc(sizeof(struct variable_entry));
        enum token_names var_type = ast->child[0]->t.s.t->StateId;
        ve->var_type=var_type;
        ve->var_type_name = ast->child[0]->tk->val;
        if(var_type == TK_RECORDID){
            et->et_name=malloc(strlen("REC_DEC")+1);
            strcpy(et->et_name, "REC_DEC");
            et->et=REC_DEC;
            

            StEntry se = findST(ve->var_type_name,st);
            ve->size=0;
            if(se==NULL){
                printf(ANSI_COLOR_RED "Unknown record type %s on line %d\n" ANSI_COLOR_RESET,ve->var_type_name, ast->child[0]->tk->line_no);
                errors=true;
            }
            else{
                ve->size=se->size; //TODO
            }
        }
        else if(var_type == TK_REAL || var_type == TK_INT){
            et->et_name=malloc(strlen("VAR_DEC")+1);
            strcpy(et->et_name, "VAR_DEC");
            et->et=VAR_DEC;
            if(var_type == TK_REAL){
                ve->size=REAL_SIZE;
            }
            else{
                ve->size=INT_SIZE;
            }
        }
        et->size=ve->size;
        ve->offset = offset;
        offset+=ve->size;
        st->size+=ve->size;
        et->var_entry=ve;
        insertST(key,et,st);
        ast->type_name=ve->var_type_name;
        return;
    }
    for(int i=0;i<ast->num_child;i++){
        updateGlobalVariables(ast->child[i],st);
    }
}

//TODO parameters
//parameters and local
void updateOtherVariables(Tree ast, SymbolTable st){
    int offset=st->size;
    if(ast==NULL || st==NULL){
        return;
    }
    else if(ast->t.type=='n' && ast->t.s.nt->key==declaration && ast->num_child==2){
        if(!(ast->child[0]->t.type=='t')){
            printf("ERROR\n");
            return;
        }
        char *key=ast->child[1]->tk->val;
        StEntry et=malloc(sizeof(struct StEntry));
        variable_entry ve=malloc(sizeof(struct variable_entry));
        enum token_names var_type = ast->child[0]->t.s.t->StateId;
        ve->var_type=var_type;
        ve->var_type_name = ast->child[0]->tk->val;
        if(var_type == TK_RECORDID){
            et->et_name=malloc(strlen("REC_DEC")+1);
            strcpy(et->et_name, "REC_DEC");
            et->et=REC_DEC;
            

            StEntry se = findST(ve->var_type_name,st);
            ve->size=0;
            if(se==NULL){
                printf(ANSI_COLOR_RED "Unknown record type %s on line %d\n" ANSI_COLOR_RESET,ve->var_type_name, ast->child[0]->tk->line_no);
                errors=true;
            }
            else{
                ve->size=se->size; //TODO
            }
        }
        else if(var_type == TK_REAL || var_type == TK_INT){
            et->et_name=malloc(strlen("VAR_DEC")+1);
            strcpy(et->et_name, "VAR_DEC");
            et->et=VAR_DEC;
            if(var_type == TK_REAL){
                ve->size=REAL_SIZE;
            }
            else{
                ve->size=INT_SIZE;
            }
        }
        et->size=ve->size;
        ve->offset = offset;
        offset+=ve->size;
        st->size+=ve->size;
        et->var_entry=ve;
        insertST(key,et,st);
        ast->type_name=ve->var_type_name;
        return;
    }
    for(int i=0;i<ast->num_child;i++){
        updateOtherVariables(ast->child[i],st);
    }
}


SymbolTable genSymbolTableFromFile(char *filename){
    Tree ast = getASTFromFile(filename);
    if(errors==true){
        printf(ANSI_COLOR_RED "Errors while creating AST!\n" ANSI_COLOR_RESET);
    }
    SymbolTable st = genSymbolTable(ast);
    GlobalSymbolTable = st;
    CurrentSymbolTable = st;

    typeCheck(ast,st);
    return st;
}


void printSymbolTableFromFile(char *filename){
    errors=false;
    SymbolTable st=genSymbolTableFromFile(filename);
    printST(st);
    Iterator it = getIterator(st->sl);
    StEntry se=NULL;
    while(hasNext(it)){
        se=(StEntry)getNext(it)->d;
        if(se->et==FUN_DEF){
            printf("\n");
            printST(((function_entry)se->var_entry)->symbol_table);
        }
        it=next(it);
    }
    if(errors==false){
        printf(ANSI_COLOR_GREEN "Symbol table generated successfully!\n" ANSI_COLOR_RESET);
    }
    else{
        printf(ANSI_COLOR_RED "Errors while creating symbol table!\n" ANSI_COLOR_RESET);
    }
    fflush(stdout);
}