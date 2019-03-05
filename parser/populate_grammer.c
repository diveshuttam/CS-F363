#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include "token.h"
#include "populate_grammer.h"
#include <string.h>

void print_grammer_rule(grammerRule gr){
	printf("grammer rule: ");
	printf("%d %s:%d --> ",gr.id, gr.lhs.name,gr.lhs.key);
	for(int i=0;i<gr.num_of_rhs;i++){
		char type=gr.rhs[i].type;
		if(type=='t'){
			printf("%s:%d ",gr.rhs[i].s.t.name,gr.rhs[i].s.t.StateId);
		}
		else if(type=='n'){
			printf("%s:%d ",gr.rhs[i].s.nt.name,gr.rhs[i].s.nt.key);
		}
	}
	printf("\n");
}
void follows(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char **terminals_map, hashTable ht_non_terminals,hashTable ht_terminals){
	FILE *fp;
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;
	fp = fopen(FOLLOWS_FILE,"r");
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;;
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			i = findHT(pch,ht_non_terminals);
			non_terminals[i].follows_size=0;
			non_terminals[i].follows = malloc(sizeof(Terminal)*MAX_RHS);
			int j = 0 ;
			printf("%s ", pch);
			fflush(stdout);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i].follows[j] = terminals[findHT(pch,ht_terminals)];
				non_terminals[i].follows_size++;
				printf("%s %d ",non_terminals[i].follows[j].name,non_terminals[i].follows[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			printf("\n");
		}

	}else printf("err");
	fclose(fp);
}

void firsts(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char** terminals_map,hashTable ht_non_terminals, hashTable ht_terminals){
	int i = 0;
	char* line = malloc(sizeof(char)*LINE_SIZE);
	size_t len = 0;
	size_t read;
	FILE *fp;
	
	fp = fopen(FIRSTS_FILE,"r");
	line[0] = '1';
	if(fp != NULL && (line[0]!='\n') && (line[0]!='\0')){
		line = NULL;
		len = 0 ;
		char* pch = NULL;

		while((read = getline(&line,&len,fp)) != -1 && (read!=0)){
			pch = strtok(line," \n");
			i = findHT(pch,ht_non_terminals);
			non_terminals[i].firsts=malloc(sizeof(Terminal)*MAX_RHS);
			non_terminals[i].firsts_size=0;
			int j = 0 ;
			printf("%s ",pch);
			pch = strtok(NULL," \n");
			
			while(pch != NULL){
				non_terminals[i].firsts[j]=terminals[findHT(pch,ht_terminals)];
				non_terminals[i].firsts_size++;
				printf("%s %d ",non_terminals[i].firsts[j].name,non_terminals[i].firsts[j].StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			printf("\n");
		}
	}else printf("err");
	fclose(fp);
}

grammerRule* grammer(NonTerminal* non_terminals, Terminal* terminals, char** non_terminals_map, char** terminals_map,hashTable ht_non_terminals, hashTable ht_terminals){
	grammerRule *g;
	g=malloc(sizeof(grammerRule)*NO_OF_RULES);
	FILE *fp;
	int i = 0;
	char* line = malloc(sizeof(char)*LINE_SIZE);
	size_t len = 0;
	size_t read;
	fp = fopen(GRAMMER_FILE,"r");
	line[0] = '1';
	int count=0;
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;
		while((read = getline(&line,&len,fp)) != -1){
			printf("for rule %s\n",line);
			pch = strtok(line," \n");
			char *pch1= strtok(NULL," \n");
			if(strcmp(pch1, "===>")!=0){
				printf("error %s hola %s\n",pch1,line);
				exit(0);
			}
			int nt = findHT(pch,ht_non_terminals);
			g[count].lhs=non_terminals[nt];
			g[count].rhs=malloc(sizeof(TnT)*TOKEN_SIZE);
			g[count].num_of_rhs=0;
			g[count].id=count;
			int j = 0 ;
			printf("n:%d:%s ===> ",nt,pch);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				int nt=findHT(pch,ht_non_terminals);
				int t=findHT(pch,ht_terminals);
				if(t==-1 && nt==-1 || t!=-1 && nt!=-1){
					printf("error%s\n",pch);
					exit(1);
				}
				if(t!=-1){
					g[count].rhs[j].type='t';
					g[count].rhs[j].s.t=terminals[t];
					printf("t:%d:%s ",terminals[t].StateId,terminals[t].name);
				}
				else if(nt!=-1){
					g[count].rhs[j].type='n';
					g[count].rhs[j].s.nt=non_terminals[nt];
					printf("n:%d:%s ",non_terminals[nt].key,non_terminals[nt].name);
				}
				j++;
				g[count].num_of_rhs++;
				pch = strtok(NULL," \n");
			}
			count++;
			printf("\n");
		}

	}else printf("err");
	fclose(fp);
	return g;
}

char **get_non_terminals_map(){
	char** non_terminals_map=malloc(sizeof(char*)*NO_OF_NON_TERMINALS);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		non_terminals_map[i]=malloc(sizeof(char)*TOKEN_SIZE);
		strcpy(non_terminals_map[i],"");
	}
	FILE* fp = fopen(NON_TERMINALS_FILE,"r");
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;
	if(fp != NULL){
		while((read = getline(&line,&len,fp)) != -1 && read !=0){
			if(non_terminals_map[i]==NULL){
				printf("ERROR");
				exit(0);
			}
			line[read-1]='\0';
			if(line==NULL){
				printf("ERROR line is null");
			}
			strcpy(non_terminals_map[i],line);
			if(non_terminals_map[i]==NULL){
				printf("ERRROR");
				exit(0);
			}
			i++;
		}
	}else printf("err");
	fclose(fp);
	return non_terminals_map;
}

void initialize_tnt(NonTerminal *non_terminals,Terminal *terminals,char **terminals_map,char **non_terminals_map,hashTable ht_terminals,hashTable ht_non_terminals){
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		int k=findHT(non_terminals_map[i],ht_non_terminals);
		printf("assigning %s with key %d\n",non_terminals_map[i],k);
		fflush(stdout);
		if(k!=-1){
			non_terminals[i].name=malloc(sizeof(char)*TOKEN_SIZE);
			strcpy(non_terminals[i].name,non_terminals_map[i]);
			non_terminals[i].key=k;
		}
		else{
			non_terminals[i].name=NULL;
			non_terminals[i].key=-1;
		}
		
	}

	for(int i=0;i<NO_OF_TERMINALS;i++){
		int k=findHT(terminals_map[i],ht_terminals);
		printf("assigning terminal %s with key %d\n",terminals_map[i],k);
		fflush(stdout);
		if(k!=-1){
			terminals[i].name=terminals_map[i];
			terminals[i].StateId=findHT(terminals_map[i],ht_terminals);
		}else{
			terminals[i].name=NULL;
			terminals[i].StateId=-1;
		}
	}
}


// int main()
// {
// 	grammerRule *g=get_grammer();
// }