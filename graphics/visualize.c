#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"
#include "tree_to_json.h"

bool errors=false;

int main (int argc, char *argv[])
{
  if(argc!=3){
    printf("Invalid arguments\n");
    printf("Usage %s testcasefile.txt outputfile.json\n\n",argv[0]);
    return 1;
  }
  printParseTreeForHTML(argv[1],argv[2]);
  return 0;
} 