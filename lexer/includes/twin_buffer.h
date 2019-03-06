#ifndef __TWIN_BUFFER_H
#define __TWIN_BUFFER_H
#include<stdbool.h>
#include<stdio.h>
#include"lexerDef.h"

typedef struct Stream *Stream;
Stream getStream(const char *filename);
char getChar(Stream s);
char retractChar(Stream s);
bool isEofStream(const Stream s); //current char is not eof
#endif