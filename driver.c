#include"lexerDef.h"
#include<stdio.h>
int main()
{   Token tk;
    while((tk = get_next_token())!=EOF)
    {
        if(tk.currentState=="-1")
        {
            printf("Error Occured");
        }
        else
        {
            printf("%s",tk.Token);
        }
    }
}