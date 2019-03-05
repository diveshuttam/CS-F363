#include "Stack.h"
#include "SeqList.h"
#include <stdlib.h>

struct Stack{
  SeqList sl;
};

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
  Stack s = malloc(sizeof(struct Stack));
  s->sl = newList ();
  return s;
}

Stack
pop (Stack s)
{
  s->sl=deleteAtFront (s->sl);
  return s;
}

Stack
push (Stack s, Element E)
{
  s->sl=insertAtFront (s->sl, E);
  return s;
}

Element
top (Stack s)
{
  return getNext (getIterator (s->sl));
}
