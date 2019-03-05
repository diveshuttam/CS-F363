#include "lexerDef.h"
#include "transition.h"
#include "populate_dfa.h"
//return NULL if encounter \O
//handle invalid_state with token state as -1
// do error detection for max token size
Token get_next_token_sub(Stream s, Transition** transition_table,State *states)
{
    State current_state=states[0];
    Token tk;
    int idx=0;
    tk.val = (char*)malloc(sizeof(char)*MAX_TOKEN_SIZE);
    memset(tk.val, '\0', MAX_TOKEN_SIZE);
    tk.state=-1;
    tk.len=0;
    char ch=1;
    while(!isEofStream(s))
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
            retractChar(s);
            tk.val[idx-1] = '\0';
            tk.state = current_state.val;
            return tk;
        }
        ch=getChar(s);
        tk.val[idx++]=ch;

        Transition t = transition_table[current_state.val][ch];
        State next_state = states[t.next_state];

        //special case of invalid next state
        if(t.next_state==-1)
        {
            tk.state = -1;
            return tk;
        }

        current_state = next_state;
    }
    if(current_state.is_final_state==true){
        tk.state=current_state.val;
        return tk;
    }
    tk.state = -1;
    tk.val = NULL;
    return tk;
}