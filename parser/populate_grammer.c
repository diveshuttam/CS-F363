#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include "token.h"
#include "populate_grammer.h"
#include <string.h>

void print_grammer_rule(grammerRule gr){
	debug_msg("using grammer rule: ");
	debug_msg("%d %s:%d --> ",gr.id, gr.lhs->name,gr.lhs->key);
	for(int i=0;i<gr.num_of_rhs;i++){
		char type=gr.rhs[i]->type;
		if(type=='t'){
			debug_msg("%s:%d ",gr.rhs[i]->s.t->name,gr.rhs[i]->s.t->StateId);
		}
		else if(type=='n'){
			debug_msg("%s:%d ",gr.rhs[i]->s.nt->name,gr.rhs[i]->s.nt->key);
		}
	}
	debug_msg("\n");
}
void follows(NonTerminal* non_terminals, Terminal* terminals, const char** non_terminals_map, const char **terminals_map, const hashTable ht_non_terminals,const hashTable ht_terminals){
	int i = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;
	FILE *fp;
	fp = fopen(FOLLOWS_FILE,"r");
	if(fp != NULL){
		line = NULL;
		len = 0 ;
		char* pch = NULL;;
		while((read = getline(&line,&len,fp)) != -1){
			pch = strtok(line," \n");
			i = findHT(pch,ht_non_terminals);
			non_terminals[i].follows_size=0;
			non_terminals[i].follows = malloc(sizeof(Terminal*)*MAX_RHS);
			int j = 0 ;
			debug_msg("%s ", pch);
			fflush(stdout);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				non_terminals[i].follows[j] = &terminals[findHT(pch,ht_terminals)];
				non_terminals[i].follows_size++;
				debug_msg("%s %d ",non_terminals[i].follows[j]->name,non_terminals[i].follows[j]->StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			debug_msg("\n");
		}

	}else debug_msg("err");
	fclose(fp);
}

void firsts(NonTerminal* non_terminals, Terminal* terminals, const char** non_terminals_map,const char** terminals_map,const hashTable ht_non_terminals,const hashTable ht_terminals){
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
			non_terminals[i].firsts=malloc(sizeof(Terminal*)*MAX_RHS);
			non_terminals[i].firsts_size=0;
			int j = 0 ;
			debug_msg("%s ",pch);
			pch = strtok(NULL," \n");
			
			while(pch != NULL){
				non_terminals[i].firsts[j]=&terminals[findHT(pch,ht_terminals)];
				non_terminals[i].firsts_size++;
				debug_msg("%s %d ",non_terminals[i].firsts[j]->name,non_terminals[i].firsts[j]->StateId);
				j++;
				pch = strtok(NULL," \n");
			}
			debug_msg("\n");
		}
	}else debug_msg("err");
	fclose(fp);
}

grammerRule* grammer(const NonTerminal* non_terminals,const Terminal* terminals,const char** non_terminals_map, const char** terminals_map,const hashTable ht_non_terminals, const hashTable ht_terminals){
	grammerRule *g;
	g=malloc(sizeof(grammerRule)*NO_OF_RULES);
	FILE *fp;
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
			debug_msg("for line %s\n",line);
			pch = strtok(line," \n");
			char *pch1= strtok(NULL," \n");
			if(strcmp(pch1, "===>")!=0){
				debug_msg("error %s hola %s\n",pch1,line);
				exit(0);
			}
			int nt = findHT(pch,ht_non_terminals);
			g[count].lhs=(NonTerminal*)&non_terminals[nt];
			g[count].rhs=malloc(sizeof(TerminalNonTerminal*)*MAX_RHS);
			g[count].num_of_rhs=0;
			g[count].id=count;
			int j = 0 ;
			debug_msg("n:%d:%s ===> ",nt,pch);
			pch = strtok(NULL," \n");
			while(pch != NULL){
				int nt=findHT(pch,ht_non_terminals);
				int t=findHT(pch,ht_terminals);
				if((t==-1 && nt==-1) || (t!=-1 && nt!=-1)){
					debug_msg("error%s\n",pch);
					exit(1);
				}
				if(t!=-1){
					g[count].rhs[j]=malloc(sizeof(TnT));
					g[count].rhs[j]->type='t';
					g[count].rhs[j]->s.t=(Terminal*)&terminals[t];
					debug_msg("t:%d:%s ",terminals[t].StateId,terminals[t].name);
				}
				else if(nt!=-1){
					g[count].rhs[j]=malloc(sizeof(TnT));
					g[count].rhs[j]->type='n';
					g[count].rhs[j]->s.nt=(NonTerminal*)&non_terminals[nt];
					debug_msg("n:%d:%s ",non_terminals[nt].key,non_terminals[nt].name);
				}
				j++;
				g[count].num_of_rhs++;
				pch = strtok(NULL," \n");
			}
			count++;
			debug_msg("\n");
		}

	}else debug_msg("err");
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
				debug_msg("ERROR");
				exit(0);
			}
			line[read-1]='\0';
			if(line==NULL){
				debug_msg("ERROR line is null");
			}
			strcpy(non_terminals_map[i],line);
			if(non_terminals_map[i]==NULL){
				debug_msg("ERRROR");
				exit(0);
			}
			i++;
		}
	}else debug_msg("err");
	fclose(fp);
	return non_terminals_map;
}

void initialize_tnt(NonTerminal *non_terminals,Terminal *terminals,const char **terminals_map,const char **non_terminals_map,const hashTable ht_terminals,const hashTable ht_non_terminals){
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		int k=findHT(non_terminals_map[i],ht_non_terminals);
		debug_msg("assigning %s with key %d\n",non_terminals_map[i],k);
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
		non_terminals[i].firsts_size=-1;
		non_terminals[i].follows_size=-1;
		non_terminals[i].follows=NULL;
		non_terminals[i].firsts=NULL;
	}

	for(int i=0;i<NO_OF_TERMINALS;i++){
		int k=findHT(terminals_map[i],ht_terminals);
		debug_msg("assigning terminal %s with key %d\n",terminals_map[i],k);
		fflush(stdout);
		if(k!=-1){
			terminals[i].name=(char *)terminals_map[i];
			terminals[i].StateId=findHT(terminals_map[i],ht_terminals);
		}else{
			terminals[i].name=NULL;
			terminals[i].StateId=-1;
		}
	}
}

//check if e is in set1;
bool isPresent(Terminal **set1,int set_size, Terminal *e){
	for (int i=0;i<set_size;i++){
		Terminal *temp=set1[i];
		if(strcmp(temp->name,e->name)==0 && e->StateId==temp->StateId){
			return true;
		}
	}
	return false;
}

void findFirst(NonTerminal* nt,grammerRule* grammerRules, Terminal *eps){
	//firstSet is the set of firsts with size MAX_RHS,to be assigned before calling
	// nextPos is the position to write next terminal in firstSet i.e actual size of firstSet
	//grammerRules is the set of all grammer Rules
	//T is the terminal or non-terminal for which we are trying to find first set
	int i;
	//
	if(nt->firsts_size!=-1){
		return;
	}
	int count=0;
	for(i=0;i<NO_OF_RULES;i++){
		if(strcmp(nt->name,grammerRules[i].lhs->name)==0){
			int isEps=1;
			if(nt->firsts==NULL){
				Terminal **firstSet=malloc(sizeof(Terminal*)*MAX_FF);
				nt->firsts=firstSet;
				nt->firsts_size=0;
			}
			
			grammerRule current_rule=grammerRules[i];
			for(int j=0;j<current_rule.num_of_rhs && isEps==1;j++){
				isEps=0;
				TerminalNonTerminal *temp=current_rule.rhs[j];
				if(temp->type=='t'){ 
					if(isPresent(nt->firsts ,nt->firsts_size, temp->s.t)==false){
						nt->firsts[count++]=temp->s.t;
						nt->firsts_size=count;
						debug_msg("adding %s:%d to firsts of %s:%d\n",temp->s.t->name,temp->s.t->StateId,nt->name,nt->key);
					}
				}
				else{
					debug_msg("finding firsts of %s:%d for firsts of %s:%d\n",temp->s.nt->name,temp->s.nt->key,nt->name,nt->key);
					NonTerminal *subFirst=current_rule.rhs[j]->s.nt;
					findFirst(subFirst, grammerRules,eps);
					for(int i=0;i<subFirst->firsts_size;i++)
					{
						if(subFirst->firsts[i]->StateId==TK_EPS){
							isEps=1;
							debug_msg("%s:%d is nullable\n",subFirst->name,subFirst->key);
							continue;
						}
						if(isPresent(nt->firsts ,nt->firsts_size, subFirst->firsts[i])==false){
							nt->firsts[count++]=subFirst->firsts[i];
							nt->firsts_size=count;
						}
					}
					//Say for a rule X->Y1Y2Y3...YN,found a first set for Y1
					//check if epsilon is in the first Set
				}
			}
			if(isEps==1){
				nt->firsts[count++]=eps;
				nt->firsts_size+=1;
			}
		}
	}
 }

//assuming firsts are already calculated

void findFollow(NonTerminal* nt,grammerRule* grammerRules, Terminal *eps, Terminal *dollar){
	//firstSet is the set of firsts with size MAX_RHS,to be assigned before calling
	// nextPos is the position to write next terminal in firstSet i.e actual size of firstSet
	//grammerRules is the set of all grammer Rules
	//T is the terminal or non-terminal for which we are trying to find first set
	int i;
	//
	int count=0;
	if(nt->follows_size!=-1){
		return;
	}
	if(nt->key == program){
		nt->follows = malloc(sizeof(Terminal*)*MAX_FF);
		nt->follows[count] = dollar;
		nt->follows_size=1;
		return ;
	}
	for(i=0;i<NO_OF_RULES;i++){
		grammerRule *temp=&grammerRules[i];
		int isEps=0;
		for(int j=0;j<temp->num_of_rhs;j++){
			TerminalNonTerminal *tnt=temp->rhs[j];
			if(tnt->type=='n'){
				NonTerminal *nt1=tnt->s.nt;
				if(strcmp(nt->name,nt1->name)==0){
					isEps=1;
					if(nt->follows==NULL){
						Terminal **followSet=malloc(sizeof(Terminal*)*MAX_FF);
						nt->follows=followSet;
					}

					for(; j<(temp->num_of_rhs-1) && isEps==1;j++){
						isEps=0;
						tnt=(temp->rhs)[j+1];
						if(tnt->type=='t'){ 
							if(isPresent(nt->follows ,nt->follows_size, tnt->s.t)==false){
								nt->follows[count++]=tnt->s.t;
								nt->follows_size=count;
								debug_msg("adding %s:%d to follow of %s:%d\n",tnt->s.t->name,tnt->s.t->StateId,nt->name,nt->key);
							}
						}
						else{
							debug_msg("finding firsts of %s:%d for follows of %s:%d\n",tnt->s.nt->name,tnt->s.nt->key,nt->name,nt->key);
							NonTerminal *subFirst=tnt->s.nt;
							findFirst(subFirst, grammerRules,eps);
							for(int i=0;i<subFirst->firsts_size;i++)
							{
								if(subFirst->firsts[i]->StateId==TK_EPS){
									isEps=1;
									debug_msg("%s:%d is nullable\n",subFirst->name,subFirst->key);
									continue;
								}
								if(isPresent(nt->follows ,nt->follows_size, subFirst->firsts[i])==false){
									nt->follows[count++]=subFirst->firsts[i];
									nt->follows_size=count;
								}
							}
							//Say for a rule X->Y1Y2Y3...YN,found a first set for Y1
							//check if epsilon is in the first Set
						}
					}
					
				}
				
			}
			
		}
		if(isEps==1){
			//add follows of lhs to nt
			NonTerminal *subFollows=temp->lhs;
			debug_msg("finding follows of %s:%d for follows of %s:%d\n",subFollows->name,subFollows->key,nt->name,nt->key);
				findFollow(subFollows, grammerRules,eps,dollar);
				for(int i=0;i<subFollows->follows_size;i++)
				{
					if(isPresent(nt->follows ,nt->follows_size, subFollows->follows[i])==false){
						nt->follows[count++]=subFollows->follows[i];
						nt->follows_size=count;
					}
				}
		}
	}
 }