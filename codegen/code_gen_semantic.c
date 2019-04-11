#include"code_gen.h"
#include"hash.h"
#include"parserDef.h"
void term(void* tv)
{   

}
//arithmeticExpression ===> term expPrime
void operation(void* tv)
{   
    Tree t = (Tree)tv;
    Tree id1 = t->child[0];
    Tree id2 = t->child[1];
    char* operation = (char*)malloc(sizeof(char)*10);
    if(t->tk->state==TK_PLUS)
    {
        operation = "add";
    }
    else if(t->tk->state==TK_MINUS)
    {
        operation = "sub";
    }
    else if(t->tk->state==TK_MUL)
    {
        operation = "mul";
    }
    else
    {
        operation = "div";
    }
    t->code=(char*)malloc(snprintf(NULL,0,"\n\t mov ax, [%s] \n\t \n\t %s ax,[%s] \n\t \n\t mov [%s],ax \n\t",id1->addr,operation,id2->addr,t->addr));
    sprintf(t->code,"\n\t mov ax, [%s] \n\t \n\t %s ax,[%s] \n\t \n\t mov [%s],ax \n\t");
}
void assignmentStmt(void* tv)
{
    Tree t = (Tree)tv;
    Tree id = t->child[0];
    Tree arith = t->child[1];
    char* code;
    code = (char*)malloc(snprintf(NULL,0,"\n\t mov [%s],[%s] \n\t",id->addr,arith->addr));
    t->code = arith->code;
    strcat(t->code,code);
}
void functions(void* tv)
{
    Tree t = (Tree)tv;
    int children = t->num_child;
    int i=0;
    char* code;
    for(;i<children-1;i++)
    {
        code = (char*)malloc(snprintf(NULL,0,"\n\t %s db (?) %d \n\t",t->child[i]->tk->val,t->child[i]->size));
        if(t->code==NULL)
        {
            sprintf(t->code,code);
        }
        else
        {
            strcat(t->code,code);
        }
    }
    strcat(t->code,t->child[children-1]->code);
}