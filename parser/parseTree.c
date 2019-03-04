#include"parserDef.h"
#include"lexerDef.h"
#include"Stack.h"
#include"SeqListTree.h"
struct Tree
{
    TerminalNonTerminal t;
    int num_child;
    Tree** child;
}typedef Tree;

Tree* make_node(grammerRule *r,Tree* parent)
{   
    parent = (Tree*)malloc(sizeof(Tree));
    parent->t.s.nt = r->lhs;
    TerminalNonTerminal* rhs = r->rhs;
    int len_rhs = r->rhs_size;
    parent->num_child = len_rhs;
    parent->child = (Tree**)malloc(sizeof(Tree*)*len_rhs);
    int i=0;
    for(;i<len_rhs;i++)
    {
        parent->child[i] = (Tree*)malloc(sizeof(Tree));
        parent->child[i] -> num_child=0;
        parent->child[i] -> child = NULL;
        parent->child[i] -> t = r->rhs[i];
    }
    return parent;
}

void deleteAll(Tree* root)
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

//Stack operations, parsing the token stream
Stack operations(Token* stream,int num_tokens,grammerRule table[NO_OF_NON_TERMINALS][NO_OF_TERMINALS])
{
    Stack s = newStack();
    push(s,get_bottom_symbol());
    push(s,get_start_symbol());

    Stack popped_items = newStack(); //A stack, this will help in building the tree

    int i=0;
    grammerRule gr;
    item* tnt;

    while(i<num_tokens && top(s)!=get_bottom_symbol())
    {
        tnt = top(s);
        if(tnt->t.type=='n' && !table[tnt->t.s.nt.key][stream[i].state].isError) //need to define error rule 
        {
            pop(s);
            push(popped_items,tnt);
            gr = table[tnt->t.s.nt.key][stream[i].state];
            int rhs_size = gr.rhs_size;
            int j=rhs_size;
            
            item* to_be_pushed;
            for(;j>=0;j--)
            {
                *(to_be_pushed->gr) = gr;
                to_be_pushed->t = gr.rhs[j];
            }
        }
        else if(!table[tnt->t.s.nt.key][stream[i].state].isError)
        {
            printf("Syntax Error found at line "); //line number in token structure
        }
        else
        {
            if(tnt->t.s.t.StateId!= stream[i].state) //see the definitions of state in the two definitions
            {
                printf("Syntax Error Found"); 
            }
            else
            {
                pop(s);
                push(popped_items,tnt);
                i++;
            }
        }
    }
    reverse(popped_items);
    return popped_items;
}

//returns start_symbol
item*  get_start_symbol()
{
    item* i = (item*)malloc(sizeof(item));
    i->t.type = 'n';
    i->t.s.nt.key = 0;
    return i;
}

//return bottom symbol $ feeded in as type TerminalNonTerminal
item* get_bottom_symbol()
{
    item* i = (item*)malloc(sizeof(item));
    i->t.type = 't';
    i->t.s.t.StateId = 55; //StateID for bottom of stack symbol is 55;
    i->t.s.t.name = "$";
    return i;
}

//for finding the root item that will be expanded,i.e, the non terminal to be expanded
Tree* search(Tree* root,item* i)
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
    item* send = top(popped_items);
    pop(popped_items);
    return send;
}

Tree* parseTree(Token* stream,int num_tokens,grammerRule table[NO_OF_NON_TERMINALS][NO_OF_TERMINALS])
{
    Tree* root = (Tree*)malloc(sizeof(Tree));
    Tree* ret = root;

    Stack s = operations(stream,num_tokens,table);
    root->t = get_start_symbol()->t;

    grammerRule* start_rule = get_start_rule();
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
void visit(Tree* root)
{
    if(root->t.type=='t')
    printf("%d",root->t.s.t.name);
    else 
    printf("%d",root->t.s.nt.name);
}

void inorder(Tree* root)
{
    if (root == NULL) 
        return;

    for (int i = 0; i < root->num_child; i++) 
    {
        inorder(root->child[i]);
        visit(root->child[i]);
    }
    inorder(root->child[root->num_child]);
}