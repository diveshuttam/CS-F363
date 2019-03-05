#include"parserDef.h"
#include"lexerDef.h"
#include"Stack.h"
#include"SeqList.h"
#include"populate_grammer.h"
#include "hash.h"
#include "token.h"

typedef struct Tree *Tree;

struct Tree
{
    TerminalNonTerminal t;
    int num_child;
    Tree* child;
};

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

//Stack operations, parsing the token stream
Stack operations(Token* stream,int num_tokens,grammerRule **table)
{
    Stack s = newStack();
    push(s,make_stack_element(get_bottom_symbol()));
    push(s,make_stack_element(get_start_symbol()));

    Stack popped_items = newStack(); //A stack, this will help in building the tree

    int i=0;
    grammerRule gr;
    item* tnt;

    while(i<num_tokens && get_item_form_element(top(s))!=get_bottom_symbol())
    {
        tnt = get_item_form_element(top(s));
        if(tnt->t.type=='n' && !table[tnt->t.s.nt.key][stream[i].state].isError) //need to define error rule 
        {
            pop(s);
            push(popped_items,make_stack_element(tnt));
            gr = table[tnt->t.s.nt.key][stream[i].state];
            int rhs_size = gr.num_of_rhs;
            int j=rhs_size;
            
            item* to_be_pushed; //malloc
            for(;j>=0;j--)
            {
                *(to_be_pushed->gr) = gr;
                to_be_pushed->t = gr.rhs[j];
                push(s,make_stack_element(to_be_pushed));
            }
        }
        else if(tnt->t.type=='n' && !table[tnt->t.s.nt.key][stream[i].state].isError)
        {
            printf("Syntax Error found at line "); //line number in token structure
        }
        else
        {
            if(tnt->t.type=='t' && tnt->t.s.t.StateId!= stream[i].state) //see the definitions of state in the two definitions
            {
                printf("Syntax Error Found"); 
            }
            else
            {
                pop(s);
                push(popped_items,make_stack_element(tnt));
            }
        }
        i++;
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

Tree parseTree(Token* stream,int num_tokens,grammerRule **table)
{
    Tree root = (Tree)malloc(sizeof(struct Tree));
    Tree ret = root;

    Stack s = operations(stream,num_tokens,table);
    root->t = get_start_symbol()->t;

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



int main()
{
    NonTerminal *non_terminals=malloc(sizeof(NonTerminal)*NO_OF_NON_TERMINALS);
	Terminal *terminals=malloc(sizeof(Terminal)*NO_OF_TERMINALS);
	
	char** terminals_map = get_token_names();
	char** non_terminals_map=get_non_terminals_map();

	hashTable ht_terminals=get_token_hasht();
	hashTable ht_non_terminals = newHashTable(NO_OF_NON_TERMINALS*ALPHA_INV,HASH_A,HASH_B);
	for(int i=0;i<NO_OF_NON_TERMINALS;i++){
		insert(non_terminals_map[i],i,ht_non_terminals);
	}

	initialize_tnt(non_terminals,terminals,terminals_map,non_terminals_map,ht_terminals,ht_non_terminals);

	printf("firsts\n");
	firsts(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);
	
	printf("\nfollows\n");
	follows(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);

	printf("\ngrammer\n");
	grammerRule *g=NULL;
    g=grammer(non_terminals,terminals, non_terminals_map,terminals_map,ht_non_terminals,ht_terminals);

    printf("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES);

    printf("\nprinting terminals\n");
    for(int i=0;i<NO_OF_TERMINALS;i++){
        printf("%d ",i);
        printf("%s", terminals[i].name);
        printf("\n");
    }
    printf("\nprinting nonterminals\n");
    
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        printf("%s\n", non_terminals[i].name);
    }

    printf("\nprinting parse table\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        printf("%s\t|",non_terminals[i].name);
        for(int j=0;j<NO_OF_TERMINALS;j++){
            printf("%s:%d ",terminals[j].name,table[i][j].id);
        }
        printf("\n");
    }

    printf("\ngetting token stream\n");


}