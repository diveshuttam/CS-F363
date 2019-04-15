#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"
#include "ast.h"
#include "symbolTable.h"
#include "tree_to_json.h"
#include "code_gen.h"

bool errors=false;
int main (int argc, char *argv[])
{
  int choice;
  if(argc!=3){
    printf("Invalid arguments\n");
    printf("Usage %s testcasefile asmfile\n\n",argv[0]);
    return 1;
  }
  FILE *fp = fopen(argv[1],"r");
  if(fp==NULL){
    printf(ANSI_COLOR_RED "ERROR! "ANSI_COLOR_RESET "Cannot open file: "ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "\nExiting...\n", argv[1]);
    exit(1);
  }
  char s[2000];
  while(true){
    errors=false;
    printf(ANSI_COLOR_CYAN "Welcome to G34 Compiler!\nFunctions Availible:\n");
    printf("1: Print the token list\n");
    printf("2: Print Parsed Tree\n");
    printf("3: Printing the Abstract Syntax Tree \n");
    printf("4: Display compression ratio\n");

    printf("5: Print Symbol Table\n");
    printf("6: Print Global Variables with size and offset\n");
    printf("7: Print Functions Memory Requirements\n");
    printf("8: Print Type(Record) Definitions\n");

    printf("9: Semantic Analysis and Time\n");    
    printf("10: Output assembly code to %s\n",argv[2]);

    printf("0: exit\n");

    printf(ANSI_COLOR_MAGENTA);
    printf("Some Extra functions:\n");
    printf("21: Print code with lexical errors highlighted\n");
    printf("22: Print json of parse tree to visualize\n");
    printf("23: Print json of AST to visualize\n");
    printf(ANSI_COLOR_CYAN "\n");
    printf("Enter your choice:");
    printf(ANSI_COLOR_RESET);
    scanf("%d",&choice);
    switch(choice)
    {
      case 0:
        exit(0);
      case 1:
        printTokenizedOutput(argv[1]);
        break;
      case 2:
        printParsedOutput(argv[1]);
        break;
      case 3:
        printASTOutput(argv[1]);
        break;
      case 4:
        printRatioParseAndAST(argv[1]);
        break;
      case 5:
      case 6:
      case 7:
      case 8:
        printSymbolTableFromFile(argv[1]);
        break;
      case 10:
        printCodegenFromFile(argv[1]);
      //extra choices
      case 21:
        printFileErrorsHighlight(argv[1]);
        break;
      case 22:
        sprintf(s,"%s.parse.json",argv[1]);
        print_parse_tree_json(argv[1],s);
        break;
      case 23:
        sprintf(s,"%s.ast.json",argv[1]);
        print_ast_json(argv[1],s);
        break;        
        //time taken
      default:
        printf(ANSI_COLOR_RED "Invalid choice!!\n" ANSI_COLOR_RESET);

    }
  }
  return 0;
} 