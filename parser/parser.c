#include"parserDef.h"
#include"lexerDef.h"
#include"lexer.h"
#include"Stack.h"
#include"SeqList.h"
#include"populate_grammer.h"
#include "hash.h"
#include "token.h"

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
    int error = 0;
    grammerRule gr;
    item* tnt=NULL;
    Token *tk=NULL;
    while((tk=getNextToken(token_stream))!=NULL)
    {
        if(tk->state==TK_COMMENT||tk->state==TK_DELIM)
            continue;
        // tnt = get_item_form_element(top(s));
        while(((tnt=get_item_form_element(top(s)))!=NULL && tnt!=bottom_s && tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError!=1)) //need to define error rule 
        {
            pop(s);
            Tree crr=tnt->node;
            gr=table[tnt->t.s.nt->key][tk->state];

            print_grammer_rule(gr);
            if(gr.id==-1){
                debug_msg("error in parsing");

            }
            int rhs_size = gr.num_of_rhs;
            int j=rhs_size-1;
            crr->child=malloc(sizeof(Tree)*rhs_size);
            crr->num_child=rhs_size;
            for(;j>=0;j--)
            {
                item* to_be_pushed=malloc(sizeof(struct item)); //malloc
                to_be_pushed->gr = &gr;
                to_be_pushed->t = *(gr.rhs[j]);
                if(to_be_pushed->t.type=='n' || (to_be_pushed->t.type=='t' && to_be_pushed->t.s.t->StateId!=TK_EPS)){
                    (crr->child)[j]=malloc(sizeof(struct Tree));
                    Tree tcf=(crr->child)[j];
                    to_be_pushed->node=tcf;
                    tcf->child=NULL;
                    tcf->num_child=-1;
                    tcf->t=to_be_pushed->t;
                    tcf->tk=NULL;
                    push(s,make_stack_element(to_be_pushed));
                }
            }
            if(tk->state==TK_DOLLAR)
                break;
        }
        // if(tk->state == TK_SQR){
        //     debug_msg("\nreached and tnt is %s %d \n",tnt->t.s.nt.name,tnt->t.s.nt.key);
        // 

        if(tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError==1)
        {
            // debug_msg("Syntax Error found at line y, %s %s %d\n",tnt->t.s.nt.name,tk->val,tk->state);
            debug_msg("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.nt->name,tnt->t.s.nt->key,tk->val,tk->state); 
            exit(0);
            error = 1;//line number in token structure
        }
        else
        {
            if(tnt->t.type=='t' && tnt->t.s.t->StateId!= tk->state) //see the definitions of state in the two definitions
            {
                debug_msg("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.t->name,tnt->t.s.t->StateId,tk->val,tk->state); 
                error = 1;
                // exit(0);
                item *i=NULL;
                do{
                    i=get_item_form_element(top(s));
                    pop(s);
                }while(i!=NULL && i->t.type=='t' && i->t.s.t->StateId==tk->state);
            }
            else
            {
                Tree crr=tnt->node;
                pop(s);
                if(tnt->t.type=='t' && tnt->t.s.t->StateId!=TK_EPS){
                    crr->tk=tk;
                    tnt->gr=&gr;
                }
            }
        }
    }
    if(error==0)
    {
        debug_msg("No errors!\n");
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


//root traversal
void visit(const Tree root)
{
    if(root->t.type=='t')
        {
            if(root->tk==NULL){
            printf("error with tree node %s:%d terminal Token points to NULL \n",root->t.s.t->name , root->t.s.t->StateId);
            exit(0);
            }
        printf("%s at line %d:%s\n",root->t.s.t->name,root->tk->line_no,root->tk->val);
    }
    else{ 
        printf("%s %d\n",root->t.s.nt->name, root->t.s.nt->key);
    }
}

void inorder(const Tree root){
    if (root == NULL) 
        return;
    if(root->num_child>0){
        inorder(root->child[0]);
    }
    visit(root);
    for (int i = 1; i < root->num_child; i++) 
    {
        inorder(root->child[i]);
    }
}

void printParsedOutput(char* testcase_file){
    NonTerminal *non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
	Terminal *terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);

	char** terminals_map = get_token_names();
	char** non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insert(non_terminals_map[i],i,ht_non_terminals);
	}

	initialize_tnt(non_terminals,terminals,(const char**) terminals_map,(const char**) non_terminals_map,(const hashTable) ht_terminals,(const hashTable)ht_non_terminals);

    debug_msg("\ngrammer\n");
    grammerRule *g=NULL;
    g=grammer(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("calculating firsts\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        findFirst(&non_terminals[i], g, &terminals[TK_EPS]);
    }

    debug_msg("firsts\n");
	firsts(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    // debug_msg("calculating follows\n");
    // for(int i=0;i<NO_OF_NON_TERMINALS;i++){
    //     findFollows(&non_terminals[i], g, &terminals[TK_EPS], &terminals[TK_DOLLAR]);
    // }

    debug_msg("firsts\n");
	follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,&terminals[TK_EPS]);
    debug_msg("\nprinting terminals\n");
    for(int i=0;i<NO_OF_TERMINALS;i++){
        debug_msg("%d ",i);
        debug_msg("%s", terminals[i].name);
        debug_msg("\n");
    }
    debug_msg("\nprinting nonterminals,with firsts and follows\n");

    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal curr=non_terminals[i];
        debug_msg("\n%s:%d, firsts:%d follows:%d\n", curr.name,curr.key,curr.firsts_size,curr.follows_size);
        debug_msg("firsts: ");
        for(int j=0;j<curr.firsts_size;j++){
            debug_msg("%s:%d ",curr.firsts[j]->name, curr.firsts[j]->StateId);
        }
        debug_msg("\n");
        debug_msg("follows: ");
        for(int j=0;j<curr.follows_size;j++){
            debug_msg("%s:%d ",curr.follows[j]->name, curr.follows[j]->StateId);
        }
        debug_msg("\n");
    }

    debug_msg("\nprinting parse table\n");
    for(int i=-1;i<NO_OF_NON_TERMINALS;i++){
        if(i!=-1){
            debug_msg("%s:%d,",non_terminals[i].name,non_terminals[i].key);
        }
        else
        {
            debug_msg("non_terminals,");
        }

        for(int j=0;j<NO_OF_TERMINALS;j++){
            if(terminals[j].name!=NULL){
                if(i==-1){
                    debug_msg("%s:%d,",terminals[j].name,terminals[j].StateId);
                }
                else{
                    debug_msg("%d,",table[i][j].id);
                }
            }
        }
        debug_msg("\n");
    }

    //debug_msg("\ngetting token stream\n");
    //#ifndef DEBUG
    //char* testcase_file="testcases/testcase4.txt";
	debug_msg("Input the file name to be compiled: %s \n",testcase_file);
	//#else

	//#endif

    debug_msg("printing Grammer rules\n");
    for(int i=0;i<NO_OF_RULES;i++){
        grammerRule gr=g[i];
        print_grammer_rule(gr);
    }
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    inorder(t);
 }