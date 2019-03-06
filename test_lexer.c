#include <stdio.h>
#include "lexer.h"
int main()
{
	
	#ifndef DEBUG
	char testcase_file[40];
	debug_msg("Input the file name to be compiled: \n");
	scanf("%s",testcase_file);
	#else
	char *testcase_file="testcases/testcase1.txt";
	#endif
	
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return -1;
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

