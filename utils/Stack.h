#ifndef __STACK_H
#define __STACK_H
#include "Element.h"
typedef struct Stack *Stack;

Stack newStack ();
Stack pop (Stack s);
Stack push (Stack s, Element e);
Element top (Stack s);
Stack clearStack (Stack s);

#endif
