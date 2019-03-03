#ifndef __SEQLIST_DTYPE_H
#define __SEQLIST_DTYPE_H
#include <stdlib.h>
#include "SeqList.h"


#ifndef __FREEELEMENT
#define __FREEELEMENT
void freeElement (Element e)
{
  free (e->k);
  free (e->d);
  free(e);
}
#endif


#ifndef __COMPARE
#ifndef __WITHOUT_KEY
#define __COMPARE
//compare first is less than second
int
compare (Key k1, Key k2)
{
  int K1=*(int*)k1;
  int K2=*(int*)k2;
  if (K1 < K2)
    return LESSTHAN;
  if (K1 > K2)
    return GREATERTHAN;
  if (K1 == K2)
    return EQUALTO;
}
#endif
#endif


#endif