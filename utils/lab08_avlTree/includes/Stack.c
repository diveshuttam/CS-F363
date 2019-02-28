#ifndef __STACK
#define __STACK
typedef struct SeqList *Stack;
#endif


#include "Stack.h"
#define __SEQLIST_ELEMENT
typedef StackElement SeqListElement;
#include "SeqList.h"
#include <stdlib.h>

Stack
clearStack (Stack s)
{
  while (top (s) != NULL)
    {
      s = pop (s);
    }
  return s;
}

Stack
newStack ()
{
  Stack s = newList ();
  return s;
}

Stack
pop (Stack s)
{
  return deleteAtFront (s);
}

StackElement top (Stack s);
Stack
push (Stack s, StackElement E)
{
  return insertAtFront (s, E);
}

StackElement
top (Stack s)
{
  return getNext (getIterator (s));
}

#ifndef __FREEELEMENT
#define __FREEELEMENT
void
freeElement (StackElement e)
{
  free (e);
}
#endif
