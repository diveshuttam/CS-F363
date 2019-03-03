#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"
#include "hash.h"
#include <string.h>

int main(void){
	char* non_terminals_map[51];
	FILE* fp = fopen("nonterminals.txt","r");
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	if(fp != NULL){
		while((read = getline(&line,&len,fp)) != -1){
			non_terminals_map[i] = malloc(sizeof(char)*read);
			printf("%s --- %ld\n", line,read);	
			strcpy(non_terminals_map[i],line);
			non_terminals_map[i++][read-1]='\0';
		}
	}else printf("err");
	fclose(fp);

	hashTable* ht = newHashTable(100);
	for(i=0;i<51;i++){
		insert(non_terminals_map[i],i,ht);
	}
	printf("%d\n",findHT("program",ht,non_terminals_map,51));
}