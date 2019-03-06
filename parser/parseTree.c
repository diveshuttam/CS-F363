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
item*  get_start_symbol(const grammerRule *g)
{
    static item *i=NULL;
    if(i==NULL){
        i=malloc(sizeof(struct item));
        i->gr=(grammerRule *)g;
        i->t.type='n';
        i->t.s.nt=g[0].lhs;
        i->node=malloc(sizeof(struct Tree));
        i->node->child=NULL;
        i->node->num_child=-1;
        i->node->t=i->t;
    }
    return i;
}

//return bottom symbol $ feeded in as type TerminalNonTerminal
item* get_bottom_symbol()
{
    static item* i = NULL;
    if(i==NULL){
        i=(item*)malloc(sizeof(item));
        i->t.type = 't';
        i->t.s.t.StateId = TK_DOLLAR; //StateID for bottom of stack symbol is 55;
        i->t.s.t.name = "$";
        i->gr=NULL;
        i->node=NULL;
    }
    return i;
}

//Stack operations, parsing the token stream
Tree parseTree(Stream token_stream,const grammerRule **table,const grammerRule *g)
{
    Tree root=malloc(sizeof(struct Tree));
    Stack s = newStack();
    item *start_s=get_start_symbol(g);
    push(s,make_stack_element(get_bottom_symbol()));
    push(s,make_stack_element(start_s));
    root=start_s->node;
    int error = 0;
    int i=0;
    grammerRule gr;
    item* tnt;
    Token *tk;
    while((tk=getNextToken(token_stream))!=NULL)
    {
        if(tk->state==TK_COMMENT||tk->state==TK_DELIM)
            continue;
        // tnt = get_item_form_element(top(s));
        while(((tnt=get_item_form_element(top(s)))!=NULL && tnt!=get_bottom_symbol() && tnt->t.type=='n' && table[tnt->t.s.nt.key][tk->state].isError!=1)) //need to define error rule 
        {
            pop(s);
            Tree crr=tnt->node;
            gr=table[tnt->t.s.nt.key][tk->state];

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
                to_be_pushed->t = gr.rhs[j];
                if(to_be_pushed->t.type=='n' || (to_be_pushed->t.type=='t' && to_be_pushed->t.s.t.StateId!=TK_EPS)){
                    (crr->child)[j]=malloc(sizeof(struct Tree));
                    Tree tcf=(crr->child)[j];
                    to_be_pushed->node=tcf;
                    tcf->child=NULL;
                    tcf->num_child=-1;
                    tcf->t=to_be_pushed->t;
                    push(s,make_stack_element(to_be_pushed));
                }
            }
            if(tk->state==TK_DOLLAR)
                break;
        }
        // if(tk->state == TK_SQR){
        //     debug_msg("\nreached and tnt is %s %d \n",tnt->t.s.nt.name,tnt->t.s.nt.key);
        // 

        if(tnt->t.type=='n' && table[tnt->t.s.nt.key][tk->state].isError==1)
        {
            // debug_msg("Syntax Error found at line y, %s %s %d\n",tnt->t.s.nt.name,tk->val,tk->state);
            debug_msg("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.nt.name,tnt->t.s.nt.key,tk->val,tk->state); 
            exit(0);
            error = 1;//line number in token structure
        }
        else
        {
            if(tnt->t.type=='t' && tnt->t.s.t.StateId!= tk->state) //see the definitions of state in the two definitions
            {
                debug_msg("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.t.name,tnt->t.s.t.StateId,tk->val,tk->state); 
                error = 1;
                // exit(0);
                item *i=NULL;
                do{
                    i=get_item_form_element(top(s));
                    pop(s);
                }while(i!=NULL && i->t.type=='t' && i->t.s.t.StateId==tk->state);
            }
            else
            {
                Tree crr=tnt->node;
                pop(s);
                if(tnt->t.type=='t' && tnt->t.s.t.StateId!=TK_EPS){
                    tnt->t.s.t.tk=tk;
                    crr->t.s.t.tk=tk;
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
        if(root->child[itr]->t.s.nt.key == i->t.s.nt.key)
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
        printf("%s:%d at line %d:%s\n",root->t.s.t.name , root->t.s.t.StateId,root->t.s.t.tk->line_no,root->t.s.t.tk->val);
    else 
        printf("%s %d\n",root->t.s.nt.name, root->t.s.nt.key);
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