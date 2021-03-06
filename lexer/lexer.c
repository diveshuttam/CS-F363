#include "lexer.h"
#include "colors.h"
#include <stdio.h>


DFA* createDFA(){
	DFA *d=malloc(sizeof(struct DFA));
    FILE* fp ;
	fp = fopen(DFA_RULES_FILE,"r");
	*d = populate_dfa(fp);
    fclose(fp);
    return d;
}

Token* getNextToken(Stream s){
	static DFA *d;
	static int line_no=1;
	if(s->valid==false){
		line_no=1;
	}
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
	int a=findHTInt(tk->val,*keywords);
	if(a!=-1){
		tk->state=a;
	}
	if(tk->state==TK_ID && (strlen(tk->val)>MAX_TK_LEN)){
		tk->state=-1;
	}
	return tk;
}



void removeComments(const char *testcaseFile, const char *cleanFile){
	Stream s=getStream(testcaseFile);
	FILE *fp=fopen(cleanFile,"w");
	Token *tk;
	int state;
	char *val;
	int line_no;
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
				printf("error with token at line %d\n", line_no);
				printf("value: %s\nToken_type: %s:%d\n\n", val,"INVALID",state);
			}
		}
	};

	return;
}

void removeCommentsStdout(const char *testcaseFile){
	Stream s=getStream(testcaseFile);
	if(s==NULL){
		printf("error opening file %s\n", testcaseFile);
		return;
	}
	Token *tk;
	int state;
	char *val;
	while(((tk=getNextToken(s)) && tk!=NULL && tk->state!=TK_DOLLAR)){
		state=tk->state;
		val=tk->val;
		if(val!=NULL && state != -1){
			if(state!=TK_COMMENT){
				printf("%s",val);
			}
			// else ignore
		}
		else{
			if(state==-1){
				//invalid state
				printf(ANSI_COLOR_RED);
				printf("%s",val);
				printf(ANSI_COLOR_RESET);
			}
		}
	}
}
void printTokenizedOutput(char* testcase_file)
{
	Stream s=getStream(testcase_file);
	if(s==NULL){
		printf("error opening file %s\n", testcase_file);
	}
	Token* tk;
	int state;
	char *val;
	int num=1;
	char **token_names=get_token_names();
	while((tk=getNextToken(s)) && tk!=NULL && tk->state!=TK_DOLLAR){
		state=tk->state;
		val=tk->val;
		int line_no=tk->line_no;
		if(val!=NULL && state != -1 && state!=TK_DELIM){
				printf("token number: %d\nvalue: %s\nToken_type: %s:%d\nLine no: %d\n\n",num++, val,token_names[state],state, line_no);
			// else ignore
		}
		else{
			if(state==-1){
				errors = true;
				printf(ANSI_COLOR_RED "\nerror with token\n" ANSI_COLOR_RESET);
				printf("token number: %d\tvalue: %s\tToken_type: %s:%d\tLine no: %d\n",num, val,"INVALID",state,line_no);
			}
			fflush(stdout);
		}
		free(val);
	}
	if(errors==true){
            printf(ANSI_COLOR_RED "Errors found in tokenizing\n" ANSI_COLOR_RESET);
        }
        else{
            printf(ANSI_COLOR_GREEN "Tokenization Successful. No lexical errors.\n" ANSI_COLOR_RESET);
        }
}

void printFileErrorsHighlight(const char *testcaseFile){
	Stream s=getStream(testcaseFile);
	if(s==NULL){
		printf("error opening file %s\n", testcaseFile);
		return;
	}
	Token *tk;
	int state;
	char *val;
	while(((tk=getNextToken(s)) && tk!=NULL && tk->state!=TK_DOLLAR)){
		state=tk->state;
		val=tk->val;
		if(val!=NULL && state != -1){
				printf("%s",val);
		}
		else{
			if(state==-1){
				//invalid state
				printf(ANSI_COLOR_RED);
				printf("%s",val);
				printf(ANSI_COLOR_RESET);
			}
		}
	}
}