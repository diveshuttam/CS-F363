#ifndef __STACK
#define __STACK
typedef struct SeqList *Stack;
#endif

#include "Stack.h"
#include "includes/SeqList.h"
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

Element top (Stack s);
Stack
push (Stack s, Element E)
{
  return insertAtFront (s, E);
}

Element
top (Stack s)
{
  return getNext (getIterator (s));
}

#ifndef __COMPARE
#define __COMPARE
int
compare (Key k1, Key k2)
{
  if (k1 < k2)
    return LESSTHAN;
  if (k2 < k1)
    return GREATERTHAN;
  return EQUALTO;
}
#endif

#ifndef __FREEELEMENT
#define __FREEELEMENT
void
freeElement (Element e)
{
  free (e);
}
#endif
