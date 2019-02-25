#include "lexerDef.h"
#define MAX_CSV_TOKEN_LEN 10
#define MAX_LINE_LEN 100
#define MAX_STATES 54

enum CSVTokenType{FinalState, FinalAndRetractingState, NormalState, SingleTransition, RangeTransition, Others};

State transition[MAX_STATES][256];

struct CSVToken{
	char *Token;
	int len;
}

typedef struct CSVToken CSVToken;

char *get_next_csv_token(char *buf,int *start, int n){
	char *token=malloc(sizeof(char)*MAX_CSV_TOKEN_LEN);
	int j=0;
	while(buf[start]!=',' && start<n){
		if(buf[start]!=' ' || buf[start]!='\t')
			token[j++]=buf[start];

		start+=1;
	}
	token[j]='\0';

	return token;
}

State [][256] populate(FILE *fp)
{

	char *buf=malloc(sizeof(char)*MAX_LINE_LEN);
	do{
		int n = fscanf(fp, "%s", &buf);
		if(buf[0]=='%'){
			continue;
		}
		State si,sf;
		int start;
		char *s1=get_next_csv_token(buf,&start,n);
		char *s2=get_next_csv_token(buf,&start,n);
		char *s3=get_next_csv_token(buf,&start,n);
		
	  	si.is_final_state=false, si.is_retracting_state=false;
	  	sf.is_final_state=false, sf.is_retracting_state=false;

		if(s1[0]=='('){
			si.is_final_state=true;
		}
		if(s1[0]=='['){
			si.is_final_state=true;
			si.is_retracting_state=true;
		}
		si.current
		if(s3[0]=='('){
			si.is_final_state=true;
		}
		if(s3[0]=='['){
			si.is_final_state=true;
			si.is_retracting_state=true;
		}

		
	}while(c!=EOF);
}
