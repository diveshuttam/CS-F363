#include "SeqList.h"
#include "hash.h"
#include "parserDef.h"
#include "token.h"
#include "populate_grammer.h"
#include <string.h>

void print_grammer_rule(grammerRule gr){
	debug_msg("grammer rule: ");
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
						printf("adding %s:%d to firsts of %s:%d\n",temp->s.t->name,temp->s.t->StateId,nt->name,nt->key);
					}
				}
				else{
					printf("finding firsts of %s:%d for firsts of %s:%d\n",temp->s.nt->name,temp->s.nt->key,nt->name,nt->key);
					NonTerminal *subFirst=current_rule.rhs[j]->s.nt;
					findFirst(subFirst, grammerRules,eps);
					for(int i=0;i<subFirst->firsts_size;i++)
					{
						if(subFirst->firsts[i]->StateId==TK_EPS){
							isEps=1;
							printf("%s:%d is nullable\n",subFirst->name,subFirst->key);
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
/*
void findFollow(NonTerminal* nt,grammerRule* grammerRules, Terminal *eps, Terminal *dollar){
	//firstSet is the set of firsts with size MAX_RHS,to be assigned before calling
	// nextPos is the position to write next terminal in firstSet i.e actual size of firstSet
	//grammerRules is the set of all grammer Rules
	//T is the terminal or non-terminal for which we are trying to find first set
	int i;
	//
	if(nt->follows_size!=-1){
		return;
	}
	int count=0;
	for(i=0;i<NO_OF_RULES;i++){
		grammerRule *temp=&[i];
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
						printf("adding %s:%d to firsts of %s:%d\n",temp->s.t->name,temp->s.t->StateId,nt->name,nt->key);
					}
				}
				else{
					printf("finding firsts of %s:%d for firsts of %s:%d\n",temp->s.nt->name,temp->s.nt->key,nt->name,nt->key);
					NonTerminal *subFirst=current_rule.rhs[j]->s.nt;
					findFirst(subFirst, grammerRules,eps);
					for(int i=0;i<subFirst->firsts_size;i++)
					{
						if(subFirst->firsts[i]->StateId==TK_EPS){
							isEps=1;
							printf("%s:%d is nullable\n",subFirst->name,subFirst->key);
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
 */
 /*void findFollow(Terminal* followSet,int* nextPos,grammerRule* grammerRules,NonTerminal nt){
 	if(strcmp(nt.name,"program") == 0){
 		followSet[*nextPos].StateId = 80 ;// for TK_DOLLAR
 		char* dollar = "TK_DOLLAR";
 		followSet[*nextPos].name = (char*)malloc(sizeof(char)*(strlen("TK_DOLLAR")+1));
 		strcpy(followSet[*nextPos].name,dollar);
 		*nextPos++;
 		free(dollar);
 	}else{
 		//because generally start state does not occur in the rhs
 		int i,j;
 		for(i = 0;i<NO_OF_RULES;i++){
			
			for(j=0;j<grammerRules[i].num_of_rhs;j++){
				if(grammerRules[i].rhs[j].type == 'n'){
					//we are searching for our non terminal
					if(strcmp(grammerRules[i].rhs[j].s.nt.name,nt.name) == 0){
						// rhs[j] is our non terminal,add firsts from rhs[j+1..]
						int isEps;
						int k;
						for(k=1;k+j<grammerRules[i].num_of_rhs;k++){
							if(grammerRules[i].rhs[j+k].type == 't'){
								// symbol following nt is a terminal and hence the only follow from this rule
								followSet[*nextPos].StateId = grammerRules[i].rhs[j+k].s.t.StateId;
								followSet[*nextPos].name = (char*)malloc(sizeof(char)*(strlen(grammerRules[i].rhs[j+k].s.t.name)+1));
								strcpy(followSet[*nextPos].name,grammerRules[i].rhs[j+k].s.t.name);
								break;
							}else{
								//symbol following is a non terminal and hence we must continue adding firsts until
								// eps is found.
								Terminal* followSubset = (Terminal*)malloc(sizeof(Terminal)*MAX_RHS);
								int* nextSubPos;
								*nextSubPos=0;
								findFirst(followSubset,nextSubPos,grammerRules,grammerRules[i].rhs[j+k]);
								isEps=0;
								int n;
								for(n=0;n<*nextSubPos;n++){
	 								if(strcmp(followSubset[n].name,"TK_EPS")==0){
		 								isEps=1;
					 					break;
					 					//TK_EPS occurs at nth position
					 					//add subNextPos[0...n-1] to firstSet
	 								}
	 							}

	 							for(int m=0;m<n;m++){
	 								followSet[*nextPos].StateId = followSubset[m].StateId;
	 								followSet[*nextPos].name = (char*)malloc(sizeof(char)*(strlen(followSubset[m].name)+1));
	 								strcpy(followSet[*nextPos].name,followSubset[m].name);
	 								*nextPos++;
	 							}
	 							if(!isEps){
	 								//Symbol following X doesnt have eps in its first
	 								// Hence no need to look forward in this rule's rhs
	 								break;
	 							}
								free(followSubset);
								free(nextSubPos);
							}

						}
						if(k+j == grammerRules[i].num_of_rhs && isEps){
							// While finding follow in rule with rhs Y1Y2..X..Yn
							// All symbols after X can go to epsilon
							Terminal* trailingFollow = (Terminal*)malloc(sizeof(Terminal)*MAX_RHS);
							int* nextTrailPos ;
							*nextTrailPos = 0;
							findFollow(trailingFollow,nextTrailPos,grammerRules,grammerRules[i].lhs);
							for(int m=0;m<*nextTrailPos;m++){
								followSet[*nextPos].StateId = trailingFollow[m].StateId;
								followSet[*nextPos].name = (char*)malloc(sizeof(char)*(strlen(trailingFollow[m].name)+1));
								strcpy(followSet[*nextPos].name,trailingFollow[m].name);
								*nextPos++;
							}
						}
						
						break; //because a nonTerminal does not occur more than once in rhs
					}else continue;
				}
			}
 		}
 	}
 }*/


 /*int main()
 {
 	grammerRule* g = grammer(non_terminals_map,)
 }*/