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
	tk = get_next_token(d.transitions,d.states,buffer,fsize+1,&start);
	while(tk.state != -1 && start!=(fsize-1)){
		state = tk.state;
		val = tk.val;
		if(val != NULL && state != -1){
			printf("token %d: value: %s state:%d\n",num++, val,state);
		}
		tk = get_next_token(d.transitions,d.states,buffer,fsize+1,&start);
	}
	if(tk.state==-1){
		printf("Invalid Token\n");
	}

	free(val);
	free(buffer);
	return 0;
}

