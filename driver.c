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

	do{
		tk = get_next_token(d.transitions,d.states,buffer,fsize+1,&start);
		state = tk.state;
		val = tk.val;
		if(val != NULL && state != -1){
			printf("token number: %d\t\tvalue: %s\t\tstate: %d\n",num++, val,state);
		}
	}while(tk.state != -1 && start!=(fsize));

	if(tk.state==-1){
		printf("Invalid Token\n");
	}
	else{
		printf("lexer finished without any errors\n");
	}

	free(val);
	free(buffer);
	return 0;
}

