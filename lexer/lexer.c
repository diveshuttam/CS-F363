#include "lexer.h"
#include <stdio.h>


DFA* createDFA(){
	DFA *d=malloc(sizeof(DFA));
    FILE* fp ;
	fp = fopen(DFA_RULES_FILE,"r");
	*d = populate_dfa(fp);
    fclose(fp);
    return d;
}

Token* getNextToken(Stream s){
	static DFA *d;
	static int line_no=1;
	static hashTable keywords;
	if(d==NULL){
		d=createDFA();
	}
	Token *tk=malloc(sizeof(Token));
	*tk=get_next_token_sub(s, d->transitions, d->states);
	if(tk->state==TK_DELIM && tk->val[0]=='\n'){
		line_no=line_no+1;
	}
	tk->line_no=line_no;
	if(isEofStream(s)){
		return NULL;
	}
	static hashTable *ht=NULL;
	if(ht==NULL){
		ht=malloc(sizeof(hashTable));
		*ht=get_keyword_hasht();
	}
	int a=findHT(tk->val,*ht);
	if(a!=-1){
		tk->state=a;
	}
	return tk;
}



void removeComments(char *testcaseFile, char *cleanFile){
	Stream s=getStream(testcaseFile);
	FILE *fp=fopen(cleanFile,"w");
	Token *tk;
	int state;
	int line_no;
	char *val;
	while(tk=(getNextToken(s))){
		state=tk->state;
		val=tk->val;
		line_no=tk->line_no;
		if(val!=NULL && state != -1){
			if(state!=TK_COMMENT){
				fprintf(fp,"%s",val);
			}
			// else ignore
		}
		else{
			if(state==-1){
				printf("error with token at line %d\n", line_no);
				printf("value: %s\nToken_type: %s:%d\n\n", val,"INVALID",state);
			}
		}
	};

	return;
}