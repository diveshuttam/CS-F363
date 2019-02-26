#include "lexerDef.h"
#define MAX_CSV_TOKEN_LEN 10
#define MAX_LINE_LEN 100
#define MAX_STATES 54
#define CHAR_LEN 256

char *get_next_csv_token(char *buf,int *start, int n){
	char *token=malloc(sizeof(char)*MAX_CSV_TOKEN_LEN);
	int j=0;
	while(buf[*start]!=',' && *start<n){
		if(buf[*start]!=' ' || buf[*start]!='\t'){
			token[j++]=buf[*start];
		}
		*start+=1;
	}
	token[j]='\0';
	return token;
}

DFA populate(FILE *fp)
{
	Transition **transitions=malloc(sizeof(Transition)*MAX_STATES*CHAR_LEN);
	memset(transitions, 0, sizeof(transitions)*MAX_STATES*CHAR_LEN);
	// for(int i=0;i<MAX_STATES;i++)
	// {
	// 	transitions[i]=malloc(sizeof(Transition)*CHAR_LEN);
	// 	memset(transitions[i], 0, sizeof(Transition)*CHAR_LEN);
	// }
	State *states=malloc(sizeof(State)*MAX_STATES);
	memset(states, 0, sizeof(State)*MAX_STATES);

	DFA d;
	d.states=states;
	d.transitions=transitions;
	char *buf=malloc(sizeof(char)*MAX_LINE_LEN);
	int n;
	while((n=fscanf(fp, "%s", buf))!=EOF){
		if(buf[0]=='%'){
			continue;
		}
		State si,sf;
		int start;
		char *s1=get_next_csv_token(buf,&start,n);
		char *s2=get_next_csv_token(buf,&start,n);
		char *s3=get_next_csv_token(buf,&start,n);
		
	  	si.is_final_state=false, si.is_retracting_state=0;
	  	sf.is_final_state=false, sf.is_retracting_state=false;

		if(s1[0]=='('){
			si.is_final_state=true;
		}
		if(s1[0]=='['){
			si.is_final_state=true;
			si.is_retracting_state=true;
		}
		s1[3]='\0';
		si.val=atoi(s1+1);
		if(s3[0]=='('){
			si.is_final_state=true;
		}
		if(s3[0]=='['){
			si.is_final_state=true;
			si.is_retracting_state=true;
		}
		s3[3]='\0';
		sf.val=atoi(s1+1);
		states[si.val]=si;
		states[sf.val]=sf;
		if(strlen(s2)==1){
			Transition t;
			t.current_state=si.val;
			t.next_state=sf.val;
			t.character=s2[0];
			transitions[t.current_state][t.character]=t;
		}
		else if(strcmp(s2,"other")==0){
			;
		}
		else if(s2[0]=='[' && s2[4]==']'){

		}
	}

	return d;
}

int main(){
	FILE *fp=fopen("dfa_states.ccsv", "r");
	DFA d=populate(fp);
}