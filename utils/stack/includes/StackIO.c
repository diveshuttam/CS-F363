#include "StackIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int checkRedirect;
void
printElement (Element e)
{
  //printf ("Key:%d Next:%p\n", e->k->data, e->next);
  if (e == NULL)
    printf ("nil\n");
  else
    printf ("%d\n", e->k);
}

Key
askKey ()
{
  Key data;
  fprintf (stderr, "Please enter the data value:");
  scanf ("%d", &data);
  return data;
}

Element
askElement ()
{
  Key K = askKey ();
  Element e = malloc (sizeof (struct Element));
  e->k = K;
  return e;
}

Stack
randomElements (Stack s, int noOfElements, Stack (*f) (Stack s, Element e))
{
  for (int i = 0; i < noOfElements; i++)
    {
      Element e = malloc (sizeof (struct Element));
      Key k;
      k = random () % 1000;
      e->k = k;
      s = f (s, e);
    }
  return s;
}

/// THESES LINES ARE FOR CONVIENENENCE NOT RELATED TO THE Stack
void
clrerr ()
{
  fprintf (stderr, "\033[2J\033[H");
}

void
setRedirection ()
{
  char link[256];
  ssize_t rval;
  rval = readlink ("/proc/self/fd/1", link, sizeof (link));
  link[rval] = '\0';

  char link1[256];
  rval = readlink ("/proc/self/fd/2", link1, sizeof (link1));
  link1[rval] = '\0';
  //printf("%s\n%s", link1, link);

  if (strcmp (link, link1) != 0)
    checkRedirect = 1;
  else
    checkRedirect = 0;
}

/// END OF EXTRA LINES
