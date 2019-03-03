#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include <string.h>

int main(void){
	NonTerminal* non_terminals[51];
	Terminal* terminals[100];
	char* non_terminals_map[51];
	FILE* fp = fopen("nonterminals.txt","r");
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	if(fp != NULL){
		while((read = getline(&line,&len,fp)) != -1){
			non_terminals_map[i] = malloc(sizeof(char)*read);	
			strcpy(non_terminals_map[i++],line);
		}
	}else printf("err");
	fclose(fp);

	hashTable* ht = newHashTable(100);
	for(i=0;i<51;i++){
		*ht = insert(non_terminals_map[i],i,*ht);
	}

	printf("%d\n",findHT("program")

	fp = fopen("follows.txt","r");
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			i = findHT(pch,*ht,non_terminals_map,51);
			printf("%s -- %d\n",pch,i);
			non_terminals[i] = (NonTerminal*)malloc(sizeof(NonTerminal));
			non_terminals[i]->name = (char*)malloc(sizeof(char)*strlen(pch));
			strcpy(non_terminals[i]->name,pch);
			non_terminals[i]->key = i;
			while(pch != NULL){
				pch = strtok(NULL," \n");
				
			}
		}
		free(pch);
		free(line);
	}else printf("err");
	fclose(fp);
	return 0 ;
}
