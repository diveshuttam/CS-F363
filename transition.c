#include"lexerDef.h"
//return NULL if encounter \O
//handle invalid_state with token state as -1
Token get_next_token(State transition_table[][MAX_SIZE],char* buffer,int buffersize,int* start)
{
    int current_state = 0;
    Token tk;
    int idx=0;
    tk.token_type = (char*)malloc(sizeof(char)*token_size);
    while((*start)!=buffersize)
    {
        char ch = buffer[(*start)];
        (*start)=(*start+1)%4096;
        State next_state = transition_table[current_state][ch];
        if(next_state.current_state==-1)
        {
            tk.state = -1;
            tk.token_type = NULL;
        }
        if(next_state.is_final_state==1 && next_state.is_retracting_state==1)
        {   
            (*start)--;
            tk.token_type[idx] = '\0';
            tk.state = next_state.current_state;
            return tk;
        }
        else if(next_state.is_final_state==1)
        {
            tk.token_type[idx]=='\0';
            tk.state = next_state.current_state;
            return tk;
        }
        tk.token_type[idx++] = ch;
        current_state = next_state.current_state;
    }
}
State transitiontable[4][256];
void init()
{
    State st;
    st.current_state = -1;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<256;j++)
        {
            transitiontable[i][j] = st;
        }
    }
}

int main()
{
    
}