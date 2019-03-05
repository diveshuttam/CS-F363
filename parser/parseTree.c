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

    return s1;
}

Tree make_node(grammerRule *r,Tree parent)
{
    parent = (Tree)(malloc(sizeof(struct Tree)));
    parent->t.s.nt = r->lhs;
    TerminalNonTerminal* rhs = r->rhs;
    int len_rhs = r->num_of_rhs;
    parent->num_child = len_rhs;
    parent->child = (Tree*)malloc(sizeof(Tree)*len_rhs);
    int i=0;
    for(;i<len_rhs;i++)
    {
        parent->child[i] = (Tree)malloc(sizeof(struct Tree));
        parent->child[i] -> num_child=0;
        parent->child[i] -> child = NULL;
        parent->child[i] -> t = r->rhs[i];
    }
    return parent;
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
item*  get_start_symbol(grammerRule *g)
{
    static item *i=NULL;
    if(i==NULL){
        i=malloc(sizeof(item));
        i->gr=&g[0];
        i->t.type='n';
        i->t.s.nt=g[0].lhs;
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
    }
    return i;
}

//Stack operations, parsing the token stream
Stack operations(Stream token_stream,grammerRule **table,grammerRule *g)
{
    Stack s = newStack();
    push(s,make_stack_element(get_bottom_symbol(g)));
    push(s,make_stack_element(get_start_symbol(g)));

    Stack popped_items = newStack(); //A stack, this will help in building the tree

    int i=0;
    grammerRule gr;
    item* tnt;
    Token *tk;
    while((tk=getNextToken(token_stream))!=NULL)
    {
        if(tk->state==TK_COMMENT||tk->state==TK_DELIM)
            continue;
        // tnt = get_item_form_element(top(s));
        while( (tnt=get_item_form_element(top(s)))!=NULL && tnt!=get_bottom_symbol() && tnt->t.type=='n' && !table[tnt->t.s.nt.key][tk->state].isError) //need to define error rule 
        {
            pop(s);
            push(popped_items,make_stack_element(tnt));
            gr = table[tnt->t.s.nt.key][tk->state];
            int rhs_size = gr.num_of_rhs;
            int j=rhs_size-1;
            
            
            for(;j>=0;j--)
            {
                item* to_be_pushed=malloc(sizeof(struct item)); //malloc
                to_be_pushed->gr = &gr;
                to_be_pushed->t = gr.rhs[j];
                push(s,make_stack_element(to_be_pushed));
            }
        }
        if(tnt->t.type=='n' && !table[tnt->t.s.nt.key][tk->state].isError)
        {
            printf("Syntax Error found at line "); //line number in token structure
        }
        else
        {
            if(tnt->t.type=='t' && tnt->t.s.t.StateId!= tk->state) //see the definitions of state in the two definitions
            {
                printf("Syntax Error Found"); 
            }
            else
            {
                pop(s);
                push(popped_items,make_stack_element(tnt));
            }
        }
    }
    reverse(popped_items);
    return popped_items;
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
}

item* parse_get(Stack popped_items)
{
    item* send = get_item_form_element(top(popped_items));
    pop(popped_items);
    return send;
}

Tree parseTree(Stream token_stream,grammerRule **table, grammerRule *g)
{
    Tree root = (Tree)malloc(sizeof(struct Tree));
    Tree ret = root;

    Stack s = operations(token_stream,table,g);
    root->t = get_start_symbol(g)->t;

    grammerRule* start_rule = table[0];
    make_node(start_rule,root);


    item* i = parse_get(s);
    while(i!=NULL)
    {
        if(!(i->t.type!='t'))
        {
            root = search(root,i);
            root = make_node(i->gr,root);
        }
        i = parse_get(s);
    }
    return ret;  
}


//root traversal
void visit(Tree root)
{
    if(root->t.type=='t')
    printf("%s %d\n",root->t.s.t.name, root->t.s.t.StateId);
    else 
    printf("%s %d\n",root->t.s.nt.name, root->t.s.nt.key);
}

void inorder(Tree root)
{
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