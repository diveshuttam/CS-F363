#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"
#include "ast.h"

void printJSON(Tree t, FILE *fp){
    if(t==NULL){
        fprintf(fp,"{\n\"text\": { \"name\": \"NULL\" },\n");
        fprintf(fp,"\"children\": []\n}\n");
        return;
    }

    char *s;
    if(t->t.type=='n'){
        s=t->t.s.nt->name;
    }
    else{
        s=malloc(snprintf(NULL, 0, "%s:%s",t->t.s.t->name,t->tk->val)+1);
        sprintf(s,"%s:%s",t->t.s.t->name,t->tk->val);
        //printf("%s\n",s);
    }
    fprintf(fp,"{\n");
        fprintf(fp,"\"text\": { \"name\": \"%s\" },\n",s);
        if(t->num_child>0){
            fprintf(fp,"\"collapsed\": true,\n");
            fprintf(fp,"\"children\": [\n");
            for(int i=0;i<t->num_child && t!=NULL && t->child!=NULL;i++){
                printJSON(t->child[i],fp);
                if(i!=t->num_child-1)
                    fprintf(fp,",");
            }
            fprintf(fp,"]\n");
        }
        else{
            fprintf(fp,"\"children\":[]\n");
        }
    fprintf(fp,"}\n");
}
 void printParseTreeForHTML(char* testcase_file, char *outfile){
    NonTerminal *non_terminals=NULL;
    non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
    Terminal *terminals=NULL;
    terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);

	char** terminals_map = NULL;
    terminals_map=get_token_names();

	char** non_terminals_map=NULL;
    non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = NULL;
    ht_non_terminals=newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insertInt(non_terminals_map[i],i,ht_non_terminals);
	}

	initialize_tnt(non_terminals,terminals,(const char**) terminals_map,(const char**) non_terminals_map,(const hashTable) ht_terminals,(const hashTable)ht_non_terminals);

    debug_msg("\ngrammer\n");
    grammerRule *g=NULL;
    g=grammer(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);
    debug_msg("calculating firsts\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        findFirst(&non_terminals[i], g, &terminals[TK_EPS]);
    }

    // debug_msg("firsts\n");
    // firsts(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("calculating follows\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        findFollow(&non_terminals[i], g, &terminals[TK_EPS], &terminals[TK_DOLLAR]);
    }

    debug_msg("printing firsts\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal nt=non_terminals[i];
        debug_msg("%s:\t",nt.name);
        for(int j=0;j<nt.firsts_size;j++){
            debug_msg("%s,",nt.firsts[j]->name);
        }
        debug_msg("\n");
    }

    debug_msg("__________\n\nprinting follows\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal nt=non_terminals[i];
        debug_msg("%s:\t",nt.name);
        for(int j=0;j<nt.follows_size;j++){
            debug_msg("%s,",nt.follows[j]->name);
        }
        debug_msg("\n");
    }
    // debug_msg("firsts\n");
	// follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,&terminals[TK_EPS]);
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    t=convert_parse_to_ast(t);
    FILE *fp=fopen(outfile,"w");
    if(fp==NULL){
        printf("Error opening file %s\n",outfile);
        return;
    }
    fprintf(fp,"{\n");
    fprintf(fp,"\"nodeStructure\":");
    printJSON(t,fp);
    fprintf(fp,"}\n");
 }
