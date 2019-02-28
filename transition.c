#include "lexerDef.h"
#include "transition.h"
#include "populate.h"
//return NULL if encounter \O
//handle invalid_state with token state as -1
// do error detection for max token size
Token get_next_token(Transition** transition_table,State *states,char* buffer,int buffersize,int* start)
{
    State current_state=states[0];
    Token tk;
    int idx=0;
    tk.val = (char*)malloc(sizeof(char)*MAX_TOKEN_SIZE);
    memset(tk.val, '\0', MAX_TOKEN_SIZE);
    tk.state=-1;
    tk.len=0;
    while((*start)!=buffersize)
    {
        if(current_state.is_final_state==1 && current_state.is_retracting_state==false)
        {
            tk.val[idx]=='\0';
            tk.len=idx;
            tk.state = current_state.val;
            return tk;
        }

        if(current_state.is_final_state==true && current_state.is_retracting_state==true)
        {   
            *start=(buffersize+*start-1)%(buffersize);
            tk.val[idx-1] = '\0';
            tk.state = current_state.val;
            return tk;
        }
        char ch = buffer[(*start)];
        (*start)=(*start+1)%(buffersize);
        tk.val[idx++]=ch;

        Transition t = transition_table[current_state.val][ch];
        State next_state = states[t.next_state];

        //special case of invalid next state
        if(t.next_state==-1)
        {
            tk.state = -1;
            tk.val = NULL;
            return tk;
        }

        current_state = next_state;
    }
    tk.state = -1;
    tk.val = NULL;
    return tk;
}


/*int main()
{
    FILE *fp=fopen("dfa_states.ccsv", "r");
	DFA d=populate(fp);
    FILE *fp1=fopen("test0.c", "r");
    int buffersize=4096;
    char *buffer=malloc(sizeof(char)*buffersize);
    fread(buffer,sizeof(char), buffersize,fp1) ;
    int start=0;
    Token tk = get_next_token(d.transitions, d.states, buffer, buffersize,&start);
}*/
