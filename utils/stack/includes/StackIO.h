//this module has functionality which is dependent on the defination of
//various structures
#ifndef __STACKIO_H
#define __STACKIO_H
extern int checkRedirect;
#include "../Stack.h"
Key askKey ();
Element askElement ();
void printElement (Element e);
void setRedirection ();
void clrerr ();

Stack
randomElements (Stack s, int noOfElements, Stack (*f) (Stack s, Element e));
#endif
