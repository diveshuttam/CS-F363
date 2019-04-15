#include"parserDef.h"
#include"lexerDef.h"
#include"lexer.h"
#include"Stack.h"
#include"SeqList.h"
#include"populate_grammer.h"
#include "hash.h"
#include "token.h"
#include "colors.h"
#include "ast.h"
#include "tree_utils.h"

struct item
{
    TerminalNonTerminal t;
    grammerRule* gr;
    Tree node;
}typedef item;

Element make_stack_element(item *i){
    Element e=malloc(sizeof(struct Element));
    (e->k)=(void*)i;
    return e;
}

item* get_item_form_element(Element e){
    if(e==NULL)
        return NULL;
    item *i=(item *)(e->k);
    return i;
}

Stack reverse(Stack s)
{
    Stack s1=newStack();
    while(top(s)!=NULL){
        push(s1,top(s));
        s=pop(s);
    }
    s=s1;
    return s1;
}

void deleteAll(Tree root)
{
    if(root->child!=NULL)
    {
        for(int i=0;i<root->num_child;i++)
        {
            deleteAll(root->child[i]);
        }
    }
    free(root);
}

//returns start_symbol
item*  get_start_symbol_item(const grammerRule* start_rule)
{
    static item *i=NULL;
    if(i==NULL){
        i=malloc(sizeof(struct item));
        i->gr=(grammerRule *)start_rule;
        i->t.type='n';
        i->t.s.nt=start_rule[0].lhs;
        i->node=malloc(sizeof(struct Tree));
        i->node->child=NULL;
        i->node->num_child=-1;
        i->node->t=i->t;
        i->node->tk=NULL;
        i->node->gr_no=start_rule->id;
    }
    return i;
}

//return bottom symbol $ feeded in as type TerminalNonTerminal
item* get_bottom_symbol_item(const Terminal *bottom_symbol)
{
    static item* i = NULL;
    if(i==NULL){
        i=(item*)malloc(sizeof(item));
        i->t.type = 't';
        i->t.s.t=(Terminal *)bottom_symbol;
        i->gr=NULL;
        i->node=NULL;
    }
    return i;
}

//Stack operations, parsing the token stream
Tree parseTree(Stream token_stream,const grammerRule **table,const grammerRule *g, const grammerRule *start_rule, const Terminal *bottom_symbol)
{
    Tree root=malloc(sizeof(struct Tree));
    Stack s = newStack();
    item *start_s=get_start_symbol_item(g);
    item *bottom_s=get_bottom_symbol_item(bottom_symbol);
    push(s,make_stack_element(bottom_s));
    push(s,make_stack_element(start_s));
    root=start_s->node;
    grammerRule gr;
    item* tnt=NULL;
    Token *tk=NULL;
    while((tk=getNextToken(token_stream))!=NULL)
    {
        if(tk->state==TK_COMMENT||tk->state==TK_DELIM)
            continue;
        // tnt = get_item_form_element(top(s));
        while(tk->state!=-1 && (((tnt=get_item_form_element(top(s)))!=NULL) && tnt!=bottom_s && tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError!=1)) //need to define error rule 
        {
            pop(s);
            Tree crr=tnt->node;
            
            gr=table[tnt->t.s.nt->key][tk->state];
            print_grammer_rule(gr);
            crr->gr_no=gr.id;
            int rhs_size = gr.num_of_rhs;
            int j=rhs_size-1;
            crr->child=malloc(sizeof(Tree)*rhs_size);
            for(int ch=0;ch<rhs_size;ch++){
                (crr->child)[ch]=NULL;
            }
            crr->num_child=rhs_size;
            for(;j>=0;j--)
            {
                item* to_be_pushed=malloc(sizeof(struct item)); //malloc
                to_be_pushed->gr = &gr;
                to_be_pushed->t = *(gr.rhs[j]);
                if(to_be_pushed->t.type=='n' || (to_be_pushed->t.type=='t' && to_be_pushed->t.s.t->StateId!=TK_EPS)){
                    (crr->child)[j]=malloc(sizeof(struct Tree));
                    to_be_pushed->node=(crr->child)[j];
                    (crr->child)[j]->child=NULL;
                    (crr->child)[j]->num_child=-1;
                    (crr->child)[j]->t=to_be_pushed->t;
                    (crr->child)[j]->tk=NULL;
                    push(s,make_stack_element(to_be_pushed));
                }
            }
            if(tk->state==TK_DOLLAR)
                break;
        }
        if(tk->state!=TK_DOLLAR)
        {
            // errors = true;
        }
        if(tk->state == -1)
        {
            errors=true;
            printf("Line:%d Unknown lexeme:%s\n", tk->line_no, tk->val);
            continue; 
        }

        else if(tnt!=NULL && tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError==1)
        {
            // debug_msg("Syntax Error found at line y, %s %s %d\n",tnt->t.s.nt.name,tk->val,tk->state);
            errors=true;
            printf("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.nt->name,tnt->t.s.nt->key,tk->val,tk->state);
            while(1)
                    {
                        if(table[tnt->t.s.nt->key][tk->state].can_be_eps==1)
                        {
                            pop(s);
                            break;
                        }
                        tk = getNextToken(token_stream);
                        if(tk==NULL)
                            break;
                        if(tk->state==-1)
                        {
                            printf("Line:%d Unknown lexeme:%s\n", tk->line_no, tk->val);
                            break;
                        }
                        if(table[tnt->t.s.nt->key][tk->state].isSyn==1)
                        {
                            if(table[tnt->t.s.nt->key][tk->state].part_of_first!=1)
                            {
                                pop(s);
                                break;
                            }
                            break;
                        }
                    }
        }
        else
        {
            if(tnt!=NULL && tnt->t.type=='t' && tnt->t.s.t->StateId!= tk->state) //see the definitions of state in the two definitions
            {
                errors = true;
                printf("Syntax Error Foundt at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.t->name,tnt->t.s.t->StateId,tk->val,tk->state); 
                 while(1)
                    {
                        if(tk->state!=-1 && tk->state!=tnt->t.s.t->StateId && tnt->t.type=='t')
                        {
                            pop(s);
                            tnt = get_item_form_element(top(s));
                        }else
                        {
                            break;
                        }
                    }
            }
            if(tnt!=NULL && tnt->t.type=='t' && tnt->t.s.t->StateId ==tk->state)
            {
                Tree crr=tnt->node;
                //assign_semantic_actions(crr,&gr);
                pop(s);
                if(tnt->t.type=='t' && tnt->t.s.t->StateId!=TK_EPS){
                    crr->tk=tk;
                    tnt->gr=&gr;
                }
            }
        }
    }
    return root;
}

//for finding the root item that will be expanded,i.e, the non terminal to be expanded
Tree search(Tree root,item* i)
{
    int num_child = root->num_child;
    int itr = 0;
    for(;itr<num_child;itr++)
    {
        if(root->child[itr]->t.s.nt->key == i->t.s.nt->key)
        {
            return root->child[itr];
        }
    }
    return NULL;
}

item* parse_get(Stack popped_items)
{
    item* send = get_item_form_element(top(popped_items));
    pop(popped_items);
    return send;
}

Tree getParsedTreeFromFile(char* testcase_file){
    NonTerminal *non_terminals=NULL;
    non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
    Terminal *terminals=NULL;
    terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);

	char** terminals_map = NULL;
    terminals_map=get_token_names();

	char** non_terminals_map=NULL;
    non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = NULL;
    ht_non_terminals=newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insertInt(non_terminals_map[i],i,ht_non_terminals);
	}

	initialize_tnt(non_terminals,terminals,(const char**) terminals_map,(const char**) non_terminals_map,(const hashTable) ht_terminals,(const hashTable)ht_non_terminals);

    debug_msg("\ngrammer\n");
    grammerRule *g=NULL;
    g=grammer(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);
        debug_msg("calculating firsts\n");
        for(int i=0;i<NO_OF_NON_TERMINALS;i++){
            findFirst(&non_terminals[i], g, &terminals[TK_EPS]);
        }

        // debug_msg("firsts\n");
        // firsts(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

        debug_msg("calculating follows\n");
        for(int i=0;i<NO_OF_NON_TERMINALS;i++){
            findFollow(&non_terminals[i], g, &terminals[TK_EPS], &terminals[TK_DOLLAR]);
        }

    // debug_msg("firsts\n");
	// follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,&terminals[TK_EPS]);
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return NULL;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    return t;
}

void printParsedOutput(char* testcase_file){
    Tree t = getParsedTreeFromFile(testcase_file);
    if(errors==true){
            printf(ANSI_COLOR_RED "Errors found in while parsing\n" ANSI_COLOR_RESET);
    }
    else{
        inorder(t);
        printf(ANSI_COLOR_GREEN "Parsing Successful. No Lexical/Syntactic Errors.\n" ANSI_COLOR_RESET);
    }
 }
 