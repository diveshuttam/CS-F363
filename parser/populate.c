#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include "token.h"
#include <string.h>

NonTerminal* follows(NonTerminal* non_terminals, Terminal** terminals, char** non_terminals_map, char** terminals_map, hashTable* ht){
	FILE *fp;
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;
	fp = fopen("rules/firsts.txt","r");
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
			non_terminals[i].name = (char*)malloc(sizeof(char)*strlen(pch));
			strcpy(non_terminals[i].name,pch);
			non_terminals[i].key = i;
			non_terminals[i].firsts = malloc(sizeof(Terminal)*10);
			int j = 0 ;
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i].firsts[j].name = malloc(sizeof(char)*TK_NAME_SIZE);
				non_terminals[i].firsts[j].StateId = findHT(pch,tokens,terminals_map,TYPES_OF_TOKEN);
				strcpy(non_terminals[i].firsts[j].name,pch);
				non_terminals[i].firsts_size++;
				printf("%s %d\n",non_terminals[i].firsts[j].name,non_terminals[i].firsts[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
		}
		free(pch);
		free(line);
	}else printf("err");
	fclose(fp);
	return non_terminals;
}

NonTerminal** firsts(NonTerminal** non_terminals, Terminal** terminals, char** non_terminals_map, char** terminals_map,hashTable *ht_non_terminals){
	int i = 0;
	char* line = malloc(sizeof(char)*1000);
	size_t len = 0;
	size_t read;
	FILE *fp;
	
	fp = fopen("./rules/firsts.txt","r");
	line[0] = '1';
	if(fp != NULL && (line[0]!='\n') && (line[0]!='\0')){
		line = NULL;
		len = 0 ;
		char* pch = NULL;
		hashTable* tokens = get_token_hasht();
		insert("eps",0,tokens);
		strcpy(terminals_map[0],"eps");
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			i = findHT(pch,ht,non_terminals_map,51);
			non_terminals[i] = (NonTerminal*)malloc(sizeof(NonTerminal));
			non_terminals[i]->name = (char*)malloc(sizeof(char)*strlen(pch));
			strcpy(non_terminals[i]->name,pch);
			non_terminals[i]->key = i;
			non_terminals[i]->firsts = malloc(sizeof(Terminal)*10);
			int j = 0 ;
			printf("%s ",pch);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i]->firsts[j].name = malloc(sizeof(char)*TK_NAME_SIZE);
				non_terminals[i]->firsts[j].StateId = findHT(pch,tokens,terminals_map,TYPES_OF_TOKEN);
				strcpy(non_terminals[i]->firsts[j].name,pch);
				non_terminals[i]->firsts_size++;
				printf("%s %d ",non_terminals[i]->firsts[j].name,non_terminals[i]->firsts[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			printf("\n");
		}
		free(line);
		free(pch);
	}else printf("err");
	fclose(fp);
	return non_terminals;
}

NonTerminal** grammer(NonTerminal** non_terminals, Terminal** terminals, char** non_terminals_map, char** terminals_map,hashTable *ht_non_terminals){
	grammerRule *g[51];
	FILE *fp;
	int i = 0;
	char* line = malloc(sizeof(char)*1000);
	size_t len = 0;
	size_t read;
	fp = fopen("./rules/grammer.txt","r");
	line[0] = '1';
	int count=0;
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;
		hashTable* tokens = get_token_hasht();
		insert("eps",0,tokens);
		strcpy(terminals_map[0],"eps");
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			if(strcmp(line, "===>")!=0){
				printf("error");
				break;
			}
			g[count]->lhs=
			i = findHT(pch,ht,non_terminals_map,51);
			non_terminals[i] = (NonTerminal*)malloc(sizeof(NonTerminal));
			non_terminals[i]->name = (char*)malloc(sizeof(char)*strlen(pch));
			strcpy(non_terminals[i]->name,pch);
			non_terminals[i]->key = i;
			non_terminals[i]->firsts = malloc(sizeof(Terminal)*10);
			int j = 0 ;
			printf("%s ",pch);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i]->firsts[j].name = malloc(sizeof(char)*TK_NAME_SIZE);
				non_terminals[i]->firsts[j].StateId = findHT(pch,tokens,terminals_map,TYPES_OF_TOKEN);
				strcpy(non_terminals[i]->firsts[j].name,pch);
				non_terminals[i]->firsts_size++;
				printf("%s %d ",non_terminals[i]->firsts[j].name,non_terminals[i]->firsts[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			printf("\n");
		}
		free(line);
		free(pch);
	}else printf("err");
	fclose(fp);
	return non_terminals;
}

int main(){

	NonTerminal* non_terminals[51];
	Terminal* terminals[100];
	char* non_terminals_map[51];
	char** terminals_map;
	FILE* fp = fopen("rules/nonterminals.txt","r");
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;
	if(fp != NULL){
		while((read = getline(&line,&len,fp)) != -1){
			non_terminals_map[i] = malloc(sizeof(char)*read);	
			strcpy(non_terminals_map[i],line);
			non_terminals_map[i++][read-1]='\0';
		}
	}else printf("err");
	fclose(fp);

	terminals_map = get_token_names();
	hashTable* non_terminals_ht = newHashTable(100,5,5381);
	for(i=0;i<51;i++){
		insert(non_terminals_map[i],i,ht);
	}

	firsts(non_terminals,terminals, non_terminals_map,terminals_map,ht);
	follows(non_terminals,terminals, non_terminals_map,terminals_map,ht);
	grammer();
	return 0;
}