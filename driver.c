#include <stdio.h>
#include "transition.h"
#include "populate.h"
int main()
{
	char filename[40];
	#ifndef DEBUG
	printf("Input the file name to be compiled: \n");
	scanf("%s",filename);
	#else
	strcpy(filename,"a.mylang");
	#endif

	FILE* fp ;
	fp =  fopen(filename,"r");
	fseek(fp,0,SEEK_END);
	long fsize = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char* buffer = (char*)malloc(fsize+1);
	fread(buffer,fsize,1,fp);
	fclose(fp);
	buffer[fsize]= 0;
	fp = fopen("dfa_states.ccsv","r");
	DFA d = populate(fp);
	fclose(fp);
	int start = 0;
	int state;
	char* val = NULL;
	Token tk;
	int num=1;
	#ifdef DEBUG
	printf("\n\nlexer: starting printing tokens...\n\n");
	#endif
	int line=1;
	int error = false;
	do{
		tk = get_next_token(d.transitions,d.states,buffer,fsize+1,&start);
		state = tk.state;
		val = tk.val;
		if(val != NULL && state != -1 && state!=53 && state!=11){ //invalid , delimiter , comments
			printf("token number: %d\t\tvalue: %s\t\tstate: %d\n",num++, val,state);
			free(val);
		}
		else{
			if(state==53 && val[0]=='\n'){
				line=line+1;
			}
			if(state==-1){
				error=true;
				printf("error with token at line %d\n", line);
				printf("token number: %d\t\tvalue: %s\t\tstate: %d\n",num++, val,state);
				free(val);
			}
		}
	}while(start!=(fsize));

	if(error==true){
		printf("Errors encountered by lexer\n");
	}
	else{
		printf("lexer finished without any errors\n");
	}
	destory_DFA(d);
	free(buffer);
	return 0;
}

