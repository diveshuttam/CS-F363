#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>

int main ()
{
  int choice;
  char filename[40];
  do{
    printf("1: remove comments\n");
    printf("2: tokenize output\n");
    printf("3: Print Parsed output\n");
    printf("0: exit\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
      case 0:
        exit(0);
      case 1:
        //remove_comments;
        printf("Enter testfile name to view comment less output:");
        scanf("%s",filename);
        removeCommentsStdout(filename);
        break;
      case 2:
        printf("Enter testfile name to view tokenized output:");
        scanf("%s",filename);
        printTokenizedOutput(filename);
        break;
      case 3:
        printf("Enter testfile name to view parsed output:");
        scanf("%s",filename);
        printParsedOutput(filename);
        break;
      case 4:
        break;
        //time taken

    }
  }while(1);
  return 0;
}