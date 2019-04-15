#include"code_gen.h"
#include"hash.h"
#include"parserDef.h"
#include"symbolTable.h"
#include"st_entries.h"
#include"st_utils.h"

//arithmeticExpression ===> term expPrime
void operation_cg(void* tv)
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
    t->code=(char*)malloc(snprintf(NULL,0,"\n\t mov ax, [%d ] \n\t \n\t %s  ax,[%d ] \n\t \n\t mov [%d ],ax \n\t",id1->addr,operation,id2->addr,t->addr));
    sprintf(t->code,"\n\t mov ax, [%d ] \n\t \n\t %s ax,[%d ] \n\t \n\t mov [%d ],ax \n\t",id1->addr,operation,id2->addr,t->addr);
}
void assignmentStmt_cg(void* tv)
{
    Tree t = (Tree)tv;
    Tree id = t->child[0];
    Tree arith = t->child[1];
    char* code;
    code = (char*)malloc(snprintf(NULL,0,"\n\t mov [%d ],[%d ] \n\t",id->addr,arith->addr));
    t->code = arith->code;
    strcat(t->code,code);
}
void handle_io_stmt_cg(void* tv)
{
    Tree t = (Tree)tv;
    Tree id = t->child[1];
    Tree read_write = t->child[0];
    if(read_write->tk->state==TK_READ)
    {
        if(id->tk->state==TK_RECORDID)
        {
            record_def_entry rec = findST(id->tk->val,GlobalSymbolTable); 
            SeqList sl=rec->subnodes;
            Iterator it = getIterator(sl);
            char* code;
            t->code = (char*)malloc(sizeof(char));
            strcpy(t->code,"");
            while(hasNext(it)){
                Element e=getNext(it);
                variable_entry ve =(variable_entry) e->d;
                code = (char*)malloc(snprintf(NULL,0,"\n\t mov eax,3 \n\t mov ebx,0 \n\t mov ecx,input_buf \n\t int 80h \n\t mov [%d ], ecx",id->addr + ve->offset));
                sprintf(code,"\n\t mov eax,3 \n\t mov ebx,0 \n\t mov ecx,input_buf \n\t int 80h \n\t mov [%d], ecx",id->addr + ve->offset);
                strcat(t->code,code);
            }
        }
        else
        {
            t->code = (char*)malloc(snprintf(NULL,0,"\n\t mov eax,3 \n\t mov ebx,0 \n\t mov ecx,input_buf \n\t int 80h \n\t mov [%d], ecx",id->addr));
            sprintf(t->code,"\n\t mov eax,3 \n\t mov ebx,0 \n\t mov ecx,input_buf \n\t int 80h \n\t mov [%d], ecx",id->addr);
        }
    }
    else
    {
        if(id->tk->state==TK_RECORDID)
        {
            record_def_entry rec = findST(id->tk->val,GlobalSymbolTable);
            SeqList sl = rec->subnodes;
            Iterator it = getIterator(sl);
            char* code;
            t->code =(char*)malloc(sizeof(char));
            strcpy(t->code,"");
            while(hasNext(it))
            {
                Element e=getNext(it);
                variable_entry ve =(variable_entry) e->d;
                code = (char*)malloc(snprintf(NULL,0,"mov ax,[ebp + %d] \n\t call iprintLF",id->addr + ve->offset));
                sprintf(code,"mov ax,[ebp + %d] \n\t call iprintLF",id->addr + ve->offset);
                strcat(t->code,code);
            }
        }
        else
        {
            t->code = (char*)malloc(snprintf(NULL,0,"mov ax,[ebp + %d] \n\t call iprintLF",id->addr));
            sprintf(t->code,"mov ax,[ebp + %d] \n\t call iprintLF",id->addr);
        }
    }
}

void iteration_cg(void* tv)
{
    Tree t = (Tree)tv;

    Tree boolean = t->child[0]->child[1];
    Tree counter = t->child[0]->child[0];
    Tree checker = t->child[0]->child[2];

    t->code = (char*)malloc(snprintf(NULL,0,"\n\t while%d: \n\t mov cx,[%d ] \n\t",counter->addr,boolean->tk->line_no));
    sprintf(t->code,"\n\t while: \n\t mov cx,[%d ] \n\t",counter->addr);
    strcat(t->code,t->child[1]->code);
    strcat(t->code,t->child[2]->code);
    char jmp_line[100];
    if(boolean->tk->state==TK_LE)
    {
        sprintf(jmp_line,"\n\t cmp cx,[%d ] \n\t jle while \n\t",checker->addr);
        strcat(t->code,jmp_line);
    }
    else if(boolean->tk->state==TK_GE)
    {
        sprintf(jmp_line,"\n\t cmp cx,[%d ] \n\t jge while \n\t",checker->addr);
        strcat(t->code,jmp_line);
    }else if(boolean->tk->state==TK_NE)
    {
        sprintf(jmp_line,"\n\t cmp cx,[%d ] \n\t jne while \n\t",checker->addr);
        strcat(t->code,jmp_line);
    }
}
void functions_cg(void* tv)
{
    Tree t = (Tree)tv;
    int children = t->num_child;
    int i=0;
    char* code;
    for(;i<children-1;i++)
    {
        code = (char*)malloc(snprintf(NULL,0,"\n\t %s  db (?) %d \n\t",t->child[i]->tk->val,t->child[i]->size));
        sprintf(code,"\n\t %s  db (?) %d \n\t",t->child[i]->tk->val,t->child[i]->size); //change
        if(t->code==NULL)
        {
            t->code = (char*)malloc(sizeof(char));
            strcpy(t->code,"");
            sprintf(t->code,code,t->child[i]->tk->val,t->child[i]->size);
        }
        else
        {
            strcat(t->code,code);
        }
    }
    strcat(t->code,t->child[children-1]->code);
}
