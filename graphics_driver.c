#include "lexerDef.h"
#include "parserDef.h"
#include "populate_grammer.h"
#include "lexer.h"
#include <stdio.h>
#include "colors.h"

int main (int argc, char *argv[])
{
  if(argc!=3){
    printf("Invalid arguments\n");
    printf("Usage ./graphics_driver testcasefile outputfile\n\n");
    return 1;
  }
  printParseTreeForHTML(argv[1],argv[2]);
  return 0;
} 