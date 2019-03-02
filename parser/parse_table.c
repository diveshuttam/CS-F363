#include"parseDef.h"

grammarRule table[NO_OF_NON_TERMINALS][NO_OF_TERMINALS];
void gen_parse_table(grammerRule *r, no_of_rules,nt_start_key, rule_start_key)
{
    int i=0;
    while(i<no_of_rules)
    {
        NonTerminal nt_current = r[i].lhs;
        TerminalNonTerminal tnt_current = r[i].rhs;

        Terminal* first = nt.first;
        Terminal* follows = nt.follows;

        
        len_firsts = len(first); //this returns the length of the first
        bool isEps = false;
        int j=0;
        for(;j<len_firsts;j++)
        {
            if(first[j].stateID!=-1)
            {
                table[nt.key][first[j].stateID] = r[i]; 
            }
            else
            {
                isEps = true;
            }
        }
        if(isEps)
        {
            grammerRule eps_rule;
            eps_rule.lhs = nt;
            eps_rule.rhs = NULL;
            int j=0;
            len_follows = len(follows);
            for(;j<len_follows;j++)
            {
                table[nt.key][follow[j].stateID] = eps_rule;
            }
        }
        i++;
        free(first);
        free(follows);
    }
}
// gen_parse_table(NonTerminals *nt, grammerRule *r, no_of_rules, no_of_nt, nt_start_key, rule_start_key){
//     firsts=nt[i].firsts
//     nt[i].follows
//     nt[i].key==i

//     parse_tabel[nt.key][firsts[idx].stateID]=rule[1]
//     r[0]=<program>--> TK_MAIN
//     //nt_start_key points to index of nterminal <program>
// }