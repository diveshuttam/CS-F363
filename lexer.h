#include<stdlib.h>
#include<stdio.h>

FILE *getStream(FILE *fp);
void getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);