#include"lexerDef.h"
#include"populate.h"
//return NULL if encounter \O
//handle invalid_state with token state as -1
Token get_next_token(Transition transition_table[][MAX_SIZE],State *states,char* buffer,int buffersize,int* start)
{
    State current_state=states[0];
    Token tk;
    int idx=0;
    tk.val = (char*)malloc(sizeof(char)*MAX_TOKEN_SIZE);
    while((*start)!=buffersize)
    {
        char ch = buffer[(*start)];
        (*start)=(*start+1)%4096;
        Transition t = transition_table[current_state.val][ch];
        
        if(t.next_state==-1)
        {
            tk.state = -1;
            tk.val = NULL;
            return tk;
        }
        State current_state = states[t.current_state];
        State next_state = states[t.next_state];

        if(next_state.is_final_state==true && next_state.is_retracting_state==true)
        {   
            (*start)--;
            tk.val[idx] = '\0';
            tk.state = next_state.val;
            return tk;
        }
        else if(next_state.is_final_state==1)
        {
            tk.val[idx]=='\0';
            tk.state = next_state.val;
            return tk;
        }
        tk.val[idx++] = ch;
        current_state = states[next_state.val];
    }
}


int main()
{
    FILE *fp=fopen("dfa_states.ccsv", "r");
	DFA d=populate(fp);
    FILE *fp1=fopen("test0.c", "r");
    int buffersize=4096;
    char *buffer=malloc(sizeof(char)*buffersize);
    fread(buffer,sizeof(char), buffersize,fp1) ;
    int start=0;
    Token tk = get_next_token(d.transitions, d.states, buffer, buffersize,&start);
}