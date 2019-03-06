#include "parserDef.h"
#include "debug.h"
#include "lexer.h"
#include "populate_grammer.h"

int main()
{
    NonTerminal *non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
	Terminal *terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);

	char** terminals_map = get_token_names();
	char** non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insert(non_terminals_map[i],i,ht_non_terminals);
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
	
    debug_msg("\n____________\n\ncalculating follows\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        findFollow(&non_terminals[i], g, &terminals[TK_EPS], &terminals[TK_DOLLAR]);
    }

    // debug_msg("firsts\n");
	// follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,&terminals[TK_EPS]);
    debug_msg("\nprinting terminals\n");
    for(int i=0;i<NO_OF_TERMINALS;i++){
        debug_msg("%d ",i);
        debug_msg("%s", terminals[i].name);
        debug_msg("\n");
    }
    debug_msg("\nprinting nonterminals,with firsts and follows\n");
    
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal curr=non_terminals[i];
        debug_msg("\n%s:%d, firsts:%d follows:%d\n", curr.name,curr.key,curr.firsts_size,curr.follows_size);
        debug_msg("firsts: ");
        for(int j=0;j<curr.firsts_size;j++){
            debug_msg("%s:%d ",curr.firsts[j]->name, curr.firsts[j]->StateId);
        }
        printf("\n");
        debug_msg("follows: ");
        for(int j=0;j<curr.follows_size;j++){
            debug_msg("%s:%d ",curr.follows[j]->name, curr.follows[j]->StateId);
        }
        printf("\n");
    }

    debug_msg("\nprinting parse table\n");
    for(int i=-1;i<NO_OF_NON_TERMINALS;i++){
        if(i!=-1){
            debug_msg("%s:%d,",non_terminals[i].name,non_terminals[i].key);
        }
        else
        {
            debug_msg("non_terminals,");
        }
        
        for(int j=0;j<NO_OF_TERMINALS;j++){
            if(terminals[j].name!=NULL){
                if(i==-1){
                    debug_msg("%s:%d,",terminals[j].name,terminals[j].StateId);
                }
                else{
                    debug_msg("%d,",table[i][j].id);
                }
            }
        }
        debug_msg("\n");
    }

    //debug_msg("\ngetting token stream\n");
    //#ifndef DEBUG
	//char testcase_file[40];
    char* testcase_file="testcases/testcase4.txt";
	debug_msg("Input the file name to be compiled: %s \n",testcase_file);
	//scanf("%s",testcase_file);
	//#else
	
	//#endif
    
    debug_msg("printing Grammer rules\n");
    for(int i=0;i<NO_OF_RULES;i++){
        grammerRule gr=g[i];
        print_grammer_rule(gr);
    }
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return -1;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    inorder(t);
}
