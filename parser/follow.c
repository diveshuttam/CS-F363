#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include "token.h"
#include <string.h>

int main(void){
	NonTerminal* non_terminals[51];
	Terminal* terminals[100];
	char* non_terminals_map[51];
	char** terminals_map;
	FILE* fp = fopen("nonterminals.txt","r");
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	if(fp != NULL){
		while((read = getline(&line,&len,fp)) != -1){
			non_terminals_map[i] = malloc(sizeof(char)*read);	
			strcpy(non_terminals_map[i],line);
			non_terminals_map[i++][read-1]='\0';
		}
	}else printf("err");
	fclose(fp);

	terminals_map = get_token_names();
	hashTable* ht = newHashTable(100);
	for(i=0;i<51;i++){
		insert(non_terminals_map[i],i,ht);
	}

	fp = fopen("firsts.txt","r");
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;
		hashTable* tokens = get_token_hasht();
		insert("$",0,tokens);
		strcpy(terminals_map[0],"$");
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			i = findHT(pch,ht,non_terminals_map,51);
			non_terminals[i] = (NonTerminal*)malloc(sizeof(NonTerminal));
			non_terminals[i]->name = (char*)malloc(sizeof(char)*strlen(pch));
			strcpy(non_terminals[i]->name,pch);
			non_terminals[i]->key = i;
			non_terminals[i]->firsts = malloc(sizeof(Terminal)*10);
			int j = 0 ;
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i]->firsts[j].name = malloc(sizeof(char)*TK_NAME_SIZE);
				non_terminals[i]->firsts[j].StateId = findHT(pch,tokens,terminals_map,TYPES_OF_TOKEN);
				strcpy(non_terminals[i]->firsts[j].name,pch);
				non_terminals[i]->firsts_size++;
				printf("%s %d\n",non_terminals[i]->firsts[j].name,non_terminals[i]->firsts[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
		}
		free(pch);
		free(line);
	}else printf("err");
	fclose(fp);
	return 0 ;
}
