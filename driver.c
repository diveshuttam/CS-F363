#include "parserDef.h"
#include "debug.h"
#include "lexer.h"
#include "populate_grammer.h"

int main()
{
    NonTerminal *non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
	Terminal *terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);
	// for(int i=0;i<NO_OF_NON_TERMINALS;i++){
    //     non_terminals[i].firsts=NULL;
    //     non_terminals[i].follows=NULL;
    //     non_terminals[i].name=NULL;
    //     non_terminals[i].follows_size=0;
    //     non_terminals[i].firsts_size=0;
    //     non_terminals[i].key=-1;
    // }
    // for(int i=0;i<NO_OF_TERMINALS;i++){
    //     terminals[i].name=NULL;
    //     terminals[i].StateId=-1;
    // }

	char** terminals_map = get_token_names();
	char** non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insert(non_terminals_map[i],i,ht_non_terminals);
	}

	initialize_tnt(non_terminals,terminals,(const char**) terminals_map,(const char**) non_terminals_map,(const hashTable) ht_terminals,(const hashTable)ht_non_terminals);

	debug_msg("firsts\n");
	firsts(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);
	
	debug_msg("\nfollows\n");
	follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);
	
	debug_msg("\ngrammer\n");
	grammerRule *g=NULL;
    g=grammer(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);
	
    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,terminals[TK_EPS]);
    debug_msg("\nprinting terminals\n");
    for(int i=0;i<NO_OF_TERMINALS;i++){
        debug_msg("%d ",i);
        debug_msg("%s", terminals[i].name);
        debug_msg("\n");
    }
    debug_msg("\nprinting nonterminals\n");
    
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        debug_msg("%s\n", non_terminals[i].name);
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
    char* testcase_file="testcases/testcase3.txt";
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
    Tree t=parseTree(s,(const grammerRule**)table,g);
    inorder(t);
}
