#include "lexerDef.h"
#include "populate_dfa.h"
#include "token.h"

#ifdef DEBUG
void my_print_transition(Transition t){
	debug_msg("addding transition\t%d\t%c\t%d\n", t.current_state, t.character, t.next_state);
}
void my_print_state(State s){
	debug_msg("addding state\t%d\t%d\t%d\n", s.val, s.is_final_state, s.is_retracting_state);
}
#else
#define my_print_transition(x)
#define my_print_state(x)
#endif
char *get_next_csv_token(char *buf,int *start, int n){
	char *token=malloc(sizeof(char)*MAX_CSV_TOKEN_LEN);
	int j=0;
	while(buf[*start]!=',' && *start<n){
		if(buf[*start]!=' ' || buf[*start]!='\t'){
			token[j++]=buf[*start];
		}
		*start+=1;
	}
	*start+=1;
	token[j]='\0';
	#ifdef DEBUG
	debug_msg("Start\t%d\n",*start);
	#endif
	return token;
}

DFA populate_dfa(FILE *fp)
{
	Transition **transitions=malloc(sizeof(Transition)*MAX_STATES*CHAR_LEN);

	for(int i=0;i<MAX_STATES;i++)
	{
		transitions[i]=malloc(sizeof(Transition)*CHAR_LEN);
		for (int j=0;j<CHAR_LEN;j++){
			transitions[i][j].character=-1;
			transitions[i][j].current_state=i;
			transitions[i][j].next_state=-1;
		}
	}
	State *states=malloc(sizeof(State)*MAX_STATES);
	memset(states, 0, sizeof(State)*MAX_STATES);

	DFA d;
	d.states=states;
	d.transitions=transitions;
	char *buf=malloc(sizeof(char)*MAX_LINE_LEN);
	int n;
	while((fgets(buf,MAX_LINE_LEN,fp))!=NULL){
		n=strlen(buf)-1;
		if(buf[0]=='%'){
			continue;
		}
		if(strlen(buf)==1){
			continue;
		}
		#ifdef DEBUG
		debug_msg("size %d\n",n);
		debug_msg("printbuf\t%s\n",buf);
		#endif

		State si,sf;
		int start=0;
		char *s1=get_next_csv_token(buf,&start,n);
		char *s2=get_next_csv_token(buf,&start,n);
		char *s3=get_next_csv_token(buf,&start,n);

		#ifdef DEBUG
		debug_msg("%s\n",s1);
		debug_msg("%s\n",s2);
		debug_msg("%s\n",s3);
		#endif

	  	si.is_final_state=false, si.is_retracting_state=false;
	  	sf.is_final_state=false, sf.is_retracting_state=false;

		if(s1[0]=='('){
			si.is_final_state=true;
		}
		if(s1[0]=='['){
			si.is_final_state=true;
			si.is_retracting_state=true;
		}
		s1[4]='\0';
		si.val=atoi(s1+1);
		my_print_state(si);
		if(s3[0]=='('){
			sf.is_final_state=true;
		}
		if(s3[0]=='['){
			sf.is_final_state=true;
			sf.is_retracting_state=true;
		}
		s3[4]='\0';
		sf.val=atoi(s3+1);
		my_print_state(sf);
		states[si.val]=si;
		states[sf.val]=sf;
		int charsize=strlen(s2);
		if(charsize==1 || charsize==3){
			Transition t;
			t.current_state=si.val;
			t.next_state=sf.val;
			if(charsize==1)
				t.character=s2[0];
			if(charsize==3)
				t.character=(char)atoi(s2);
			transitions[t.current_state][(int)(t.character)]=t;
			my_print_transition(t);
		}
		else if(strcmp(s2,"other")==0){
			Transition t;
			t.current_state=si.val;
			t.next_state=sf.val;
			for(int i=0;i<CHAR_LEN;i++){
				t.character=i;
				if(transitions[t.current_state][(int)(t.character)].next_state==-1){
					transitions[t.current_state][(int)(t.character)]=t;
					my_print_transition(t);
				}
			}
		}
		else if(s2[0]=='[' && s2[4]==']' && s2[2]=='-'){
			int init=s2[1];
			int finish=s2[3];
			Transition t;
			t.current_state=si.val;
			t.next_state=sf.val;
			for(int i=init;i<=finish;i++){
				t.character=i;
				transitions[t.current_state][(int)(t.character)]=t;
				my_print_transition(t);
			}
		}
		free(s1);
		free(s2);
		free(s3);
	}
	d.token_names=get_token_names();
	d.token_ht=get_token_hasht();
	free(buf);
	return d;
}

void destory_DFA(DFA d){
	State *s = d.states;
	free(s);
	Transition **t = d.transitions;
	char **table=d.token_names;
	hashTable ht=d.token_ht;
	
    destroy_token_name_table(table);
	// destroy_token_hasht(table);
	for(int i=0;i<MAX_STATES;i++)
	{
		free(t[i]);
	}
	free(t);
	free(ht);
}