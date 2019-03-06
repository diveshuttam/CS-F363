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
	static hashTable *keywords=NULL;
	if(d==NULL){
		d=createDFA();
	}
	Token *tk=malloc(sizeof(Token));
	*tk=get_next_token_sub(s, (const Transition**)(d->transitions), d->states);
	if(tk->state==TK_DELIM && tk->val[0]=='\n'){
		line_no=line_no+1;
	}
	tk->line_no=line_no;
	if(isEofStream(s)){
		return NULL;
	}
	if(keywords==NULL){
		keywords=malloc(sizeof(hashTable));
		*keywords=get_keyword_hasht();
	}
	int a=findHT(tk->val,*keywords);
	if(a!=-1){
		tk->state=a;
	}
	return tk;
}



void removeComments(const char *testcaseFile, const char *cleanFile){
	Stream s=getStream(testcaseFile);
	FILE *fp=fopen(cleanFile,"w");
	Token *tk;
	int state;
	int line_no;
	char *val;
	while((tk=(getNextToken(s)))){
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
				debug_msg("error with token at line %d\n", line_no);
				debug_msg("value: %s\nToken_type: %s:%d\n\n", val,"INVALID",state);
			}
		}
	};

	return;
}

void removeCommentsStdout(const char *testcaseFile){
	Stream s=getStream(testcaseFile);
	if(s==NULL){
		printf("error opening file %s", testcaseFile);
		return;
	}
	Token *tk;
	int state;
	int line_no;
	char *val;
	while(((tk=getNextToken(s)) && tk!=NULL && tk->state!=TK_DOLLAR)){
		state=tk->state;
		val=tk->val;
		line_no=tk->line_no;
		if(val!=NULL && state != -1){
			if(state!=TK_COMMENT){
				printf("%s",val);
			}
			// else ignore
		}
		else{
			if(state==-1){
				debug_msg("error with token at line %d\n", line_no);
				debug_msg("value: %s\nToken_type: %s:%d\n\n", val,"INVALID",state);
			}
		}
	}
}
void printTokenizedOutput(char* testcase_file)
{
	Stream s=getStream(testcase_file);
	if(s==NULL){
		printf("error opening file %s", testcase_file);
		return;
	}
	Token* tk;
	int state;
	int line_no;
	char *val;
	int num=1;
	char **token_names=get_token_names();
	while((tk=getNextToken(s)) && tk!=NULL && tk->state!=TK_DOLLAR){
		state=tk->state;
		val=tk->val;
		line_no=tk->line_no;
		if(val!=NULL && state != -1){
			if(state!=TK_COMMENT){
				printf("token number: %d\nvalue: %s\nToken_type: %s:%d\n\n",num++, val,token_names[state],state);
				debug_msg("token number: %d\nvalue: %s\nToken_type: %s:%d\n\n",num++, val,token_names[state],state);
			}
			// else ignore
		}
		else{
			if(state==-1){
				debug_msg("error with token at line %d\n", line_no);
				debug_msg("token number: %d\nvalue: %s\nToken_type: %s:%d\n\n",num, val,"INVALID",state);
			}
			fflush(stdout);
		}
		free(val);
	}
}