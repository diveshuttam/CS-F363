//populate the table entries not defined as ErrorRule
#include"parserDef.h"
#include"populate_grammer.h"

//LHS for error rule remains
grammerRule init(grammerRule **table)
{
    grammerRule ErrorRule;
    ErrorRule.lhs.firsts=NULL;
    ErrorRule.lhs.firsts_size=0;
    ErrorRule.lhs.follows=NULL;
    ErrorRule.lhs.follows_size=0;
    ErrorRule.rhs = NULL;
    ErrorRule.num_of_rhs = 0;
    ErrorRule.isError = 1;
    ErrorRule.id=-1;
    int i=0,j=0;
    for(;i<NO_OF_NON_TERMINALS;i++)
    {
        for(;j<NO_OF_TERMINALS;j++)
        {
            table[i][j] = ErrorRule;
        }
    }
}
grammerRule** gen_parse_table(grammerRule *r, int no_of_rules)
{    
    grammerRule **table=malloc(sizeof(grammerRule*)*NO_OF_NON_TERMINALS);
    for(int i=0;i<NO_OF_NON_TERMINALS;i++)
    {
        table[i]=malloc(sizeof(grammerRule)*NO_OF_TERMINALS);
    }
    init(table);
    int i=0;
    int isEps = 0;
    while(i<no_of_rules)
    {
        NonTerminal nt_current = r[i].lhs;
        TerminalNonTerminal* tnt_current = r[i].rhs;

        Terminal* first = NULL;
        Terminal* follows = nt_current.follows;

        int len_follows = nt_current.follows_size;
        if(tnt_current[0].type=='t')
        {
            table[nt_current.key][tnt_current[0].s.t.StateId] = r[i];
            grammerRule temp=table[nt_current.key][tnt_current[0].s.t.StateId];
            printf("adding rule %s-->%s with id:%d\n",temp.lhs.name,r[i].rhs->s.t.name,temp.id);
            printf("adding rule for %d %d\n",nt_current.key,tnt_current[0].s.t.StateId);
            printf("\n");
        }
        else
        {
            first = tnt_current[0].s.nt.firsts;
            int len_first = tnt_current[0].s.nt.firsts_size;
            int j=0;
            for(;j<len_first;j++)
            {
                if(first[j].StateId!=0)
                {
                    table[nt_current.key][first[j].StateId] = r[i]; 
                }
                else
                {
                    isEps = 1;
                }
            }
        }
        if(isEps)
        {
            grammerRule eps_rule;
            eps_rule.lhs = nt_current;
            eps_rule.rhs = NULL;
            int j=0;
            for(;j<len_follows;j++)
            {
                table[nt_current.key][follows[j].StateId] = eps_rule;
            }
        }
        i++;
    }
    return table;
}
// gen_parse_table(NonTerminals *nt, grammerRule *r, no_of_rules, no_of_nt, nt_start_key, rule_start_key){
//     firsts=nt[i].firsts
//     nt[i].follows
//     nt[i].key==i

//     parse_tabel[nt.key][firsts[idx].stateID]=rule[1]
//     r[0]=<program>--> TK_MAIN
//     //nt_start_key points to index of nterminal <program>
// }