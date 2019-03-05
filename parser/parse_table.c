//populate the table entries not defined as ErrorRule
#include"parserDef.h"
#include"populate_grammer.h"

//LHS for error rule remains
grammerRule init(grammerRule **table)
{
    grammerRule ErrorRule;
    ErrorRule.lhs.firsts=NULL;
    ErrorRule.lhs.name=NULL;
    ErrorRule.lhs.firsts_size=0;
    ErrorRule.lhs.follows=NULL;
    ErrorRule.lhs.follows_size=0;
    ErrorRule.lhs.key=-1;
    ErrorRule.rhs = NULL;
    ErrorRule.num_of_rhs = 0;
    ErrorRule.isError = 1;
    ErrorRule.id=-1;
    for(int i=0;i<NO_OF_NON_TERMINALS;i++)
    {
        //
        for(int j=0;j<NO_OF_TERMINALS;j++)
        {
            //
            table[i][j] = ErrorRule;
        }
    }
}
grammerRule** gen_parse_table(const grammerRule *r, int no_of_rules, const Terminal eps)
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
        printf("\n\nrules from ");
        print_grammer_rule(r[i]);
        printf("with lhs firsts size %d\t",r[i].lhs.firsts_size);
        printf("with lhs follow size %d\n",r[i].lhs.follows_size);
        NonTerminal nt_current = r[i].lhs;
        TerminalNonTerminal* tnt_current = r[i].rhs;

        Terminal* first = NULL;
        Terminal* follows = nt_current.follows;

        int len_follows = nt_current.follows_size;
        if(tnt_current[0].type=='t')
        {
            table[nt_current.key][tnt_current[0].s.t.StateId] = r[i];
            grammerRule temp=table[nt_current.key][tnt_current[0].s.t.StateId];
            printf("adding rule for %s:%d %s:%d\n",nt_current.name,nt_current.key,tnt_current[0].s.t.name,tnt_current[0].s.t.StateId);
            print_grammer_rule(temp);
            printf("\n");
        }
        else
        {
            first = tnt_current[0].s.nt.firsts;
            int len_first = tnt_current[0].s.nt.firsts_size;
            int j=0;
            for(;j<len_first;j++)
            {
                if(first[j].StateId!=TK_EPS)
                {
                    table[nt_current.key][first[j].StateId] = r[i]; 
                    printf("adding rule for %s:%d %s:%d\n",nt_current.name,nt_current.key,first[j].name,first[j].StateId);
                    print_grammer_rule(r[i]);
                    printf("\n");
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
            eps_rule.rhs = malloc(sizeof(TerminalNonTerminal));
            eps_rule.num_of_rhs=1;
            eps_rule.id=-2;
            eps_rule.isError=false;
            eps_rule.rhs[0].type='t';
            eps_rule.rhs[0].s.t=eps;
            
            for(int j=0;j<len_follows;j++)
            {
                table[nt_current.key][follows[j].StateId] = eps_rule;
                printf("adding rule for %s:%d %s:%d\n",nt_current.name,nt_current.key,follows[j].name,follows[j].StateId);
                print_grammer_rule(eps_rule);
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