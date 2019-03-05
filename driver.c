#include "parserDef.h"
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

	initialize_tnt(non_terminals,terminals,terminals_map,non_terminals_map,ht_terminals,ht_non_terminals);

	printf("firsts\n");
	firsts(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);
	
	printf("\nfollows\n");
	follows(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);

	printf("\ngrammer\n");
	grammerRule *g=NULL;
    g=grammer(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);

    printf("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES);

    printf("\nprinting terminals\n");
    for(int i=0;i<NO_OF_TERMINALS;i++){
        printf("%d ",i);
        printf("%s", terminals[i].name);
        printf("\n");
    }
    printf("\nprinting nonterminals\n");
    
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        printf("%s\n", non_terminals[i].name);
    }

    printf("\nprinting parse table\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        printf("%s\t|",non_terminals[i].name);
        for(int j=0;j<NO_OF_TERMINALS;j++){
            printf("%s:%d ",terminals[j].name,table[i][j].id);
        }
        printf("\n");
    }

    printf("\ngetting token stream\n");
    #ifndef DEBUG
	char testcase_file[40];
	printf("Input the file name to be compiled: \n");
	scanf("%s",testcase_file);
	#else
	char *testcase_file="testcases/testcase1.txt";
	#endif
    printf("printing Grammer rules\n");
    for(int i=0;i<NO_OF_RULES;i++){
        grammerRule gr=g[i];
        print_grammer_rule(gr);
    }
	Stream s=getStream(testcase_file);
	if(s==NULL){
		printf("error opening file %s", testcase_file);
		return -1;
	}
    Tree t=parseTree(s,table,g);
    inorder(t);
}