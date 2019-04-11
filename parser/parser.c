#include"parserDef.h"
#include"lexerDef.h"
#include"lexer.h"
#include"Stack.h"
#include"SeqList.h"
#include"populate_grammer.h"
#include "hash.h"
#include "token.h"
#include "semantic_actions.h"
#include "colors.h"
#include "traversal.h"

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
        while(tk->state!=-1 && (((tnt=get_item_form_element(top(s)))!=NULL) && tnt!=bottom_s && tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError!=1)) //need to define error rule 
        {
            pop(s);
            Tree crr=tnt->node;
            
            gr=table[tnt->t.s.nt->key][tk->state];
            print_grammer_rule(gr);
            assign_semantic_actions(crr,&gr);
            if(gr.id==-1){
                debug_msg("error in parsing");

            }
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
                    (crr->child)[j]->SemanticActions=NULL;
                    (crr->child)[j]->num_rules=0;
                    push(s,make_stack_element(to_be_pushed));
                }
            }
            if(tk->state==TK_DOLLAR)
                break;
        }
        if(tk->state == -1){
            printf("Line:%d Unknown lexeme:%s", tk->line_no, tk->val);
            return root;
        }

        if(tnt->t.type=='n' && table[tnt->t.s.nt->key][tk->state].isError==1)
        {
            // debug_msg("Syntax Error found at line y, %s %s %d\n",tnt->t.s.nt.name,tk->val,tk->state);
            printf("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.nt->name,tnt->t.s.nt->key,tk->val,tk->state); 
            // exit(0);
            error = 1;//line number in token structure
            return root;
        }
        else
        {
            if(tnt->t.type=='t' && tnt->t.s.t->StateId!= tk->state) //see the definitions of state in the two definitions
            {
                printf("Syntax Error Found at %d: %s:%d  %s:%d\n",tk->line_no,tnt->t.s.t->name,tnt->t.s.t->StateId,tk->val,tk->state); 
                error = 1;
                return root;
                // exit(0);
                item *i=NULL;
                do{
                    i=get_item_form_element(top(s));
                    pop(s);
                }while(i!=NULL && i->t.type=='t' && i->t.s.t->StateId!=tk->state);
            }
            if(tnt->t.type=='t' && tnt->t.s.t->StateId ==tk->state)
            {
                Tree crr=tnt->node;
                crr->SemanticActions=NULL;
                crr->SemanticActions=0;
                // assign_semantic_actions(crr,&gr);
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
        printf(ANSI_COLOR_GREEN "Compilation Successful\n" ANSI_COLOR_RESET);
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
            return;
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
		return;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    inorder(t);
 }

void printJSON(Tree t, FILE *fp){
    if(t==NULL){
        fprintf(fp,"{\n\"text\": { \"name\": \"NULL\" },\n");
        fprintf(fp,"\"children\": []\n}\n");
        return;
    }

    char *s;
    if(t->t.type=='n'){
        s=t->t.s.nt->name;
    }
    else{
        s=malloc(snprintf(NULL, 0, "%s:%s",t->t.s.t->name,t->tk->val)+1);
        sprintf(s,"%s:%s",t->t.s.t->name,t->tk->val);
        //printf("%s\n",s);
    }
    fprintf(fp,"{\n");
        fprintf(fp,"\"text\": { \"name\": \"%s\" },\n",s);
        if(t->num_child>0){
            fprintf(fp,"\"collapsed\": true,\n");
            fprintf(fp,"\"children\": [\n");
            for(int i=0;i<t->num_child && t!=NULL && t->child!=NULL;i++){
                printJSON(t->child[i],fp);
                if(i!=t->num_child-1)
                    fprintf(fp,",");
            }
            fprintf(fp,"]\n");
        }
        else{
            fprintf(fp,"\"children\":[]\n");
        }
    fprintf(fp,"}\n");
}
 void printParseTreeForHTML(char* testcase_file, char *outfile){
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

    debug_msg("printing firsts\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal nt=non_terminals[i];
        debug_msg("%s:\t",nt.name);
        for(int j=0;j<nt.firsts_size;j++){
            debug_msg("%s,",nt.firsts[j]->name);
        }
        debug_msg("\n");
    }

    debug_msg("__________\n\nprinting follows\n");
    for(int i=0;i<NO_OF_NON_TERMINALS;i++){
        NonTerminal nt=non_terminals[i];
        debug_msg("%s:\t",nt.name);
        for(int j=0;j<nt.follows_size;j++){
            debug_msg("%s,",nt.follows[j]->name);
        }
        debug_msg("\n");
    }
    // debug_msg("firsts\n");
	// follows(non_terminals,terminals,(const char**) non_terminals_map,(const char**)terminals_map,(const hashTable)ht_non_terminals,(const hashTable)ht_terminals);

    debug_msg("\ncreating parse table\n");
    grammerRule **table=gen_parse_table(g,NO_OF_RULES,&terminals[TK_EPS]);
	Stream s=getStream(testcase_file);
	if(s==NULL){
		debug_msg("error opening file %s", testcase_file);
		return;
	}
    Tree t=parseTree(s,(const grammerRule**)table,g,&g[0],&terminals[TK_DOLLAR]);
    post_order_traversal(t);
    FILE *fp=fopen(outfile,"w");
    if(fp==NULL){
        printf("Error opening file %s\n",outfile);
        return;
    }
    fprintf(fp,"{\n");
    fprintf(fp,"\"nodeStructure\":");
    printJSON(t,fp);
    fprintf(fp,"}\n");
 }

 