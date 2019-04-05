#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"

int main (int argc, char *argv[])
{
  int choice;
  if(argc!=3){
    printf("Invalid arguments\n");
    printf("Usage ./stage1exe testcasefile outputfile\n\n");
    return 1;
  }
  do{
    printf(ANSI_COLOR_CYAN);
    printf("1: remove comments\n");
    printf("2: tokenize output\n");
    printf("3: Print Parsed output\n");
    printf("4: Time\n");
    printf("5: Print With Lexical Errors Highlighted\n");
    printf("0: exit\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    printf(ANSI_COLOR_RESET);
    switch(choice)
    {
      case 0:
        exit(0);
      case 1:
        //remove_comments
        removeCommentsStdout(argv[1]);
        break;
      case 2:
        printTokenizedOutput(argv[1]);
        break;
      case 3:
        printParsedOutput(argv[1]);
        break;
      case 4:
        break;
      case 5:
        printFileErrorsHighlight(argv[1]);
        break;
        //time taken

    }
  }while(1);
  return 0;
} 