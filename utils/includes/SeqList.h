//Author: Divesh Uttamchandani
//2016A7PS0045P

#ifndef __SEQLIST_H
#define __SEQLIST_H

#include <stdbool.h>
#include "Element.h"

#define GREATERTHAN 1
#define LESSTHAN -1
#define EQUALTO 0

typedef struct SeqList *SeqList;
typedef struct Iterator *Iterator;



SeqList newList ();
SeqList clearList (SeqList sl);
SeqList insertAtFront (SeqList sl, Element e);
SeqList insertAtEnd (SeqList sl, Element e);
SeqList deleteAtFront (SeqList sl);
Iterator getIterator (const SeqList sl);
Iterator next (Iterator it);
Element getNext (const Iterator it);
bool hasNext (const Iterator it);
SeqList insertBefore (SeqList sl, Iterator it, Element E);
SeqList deleteAfter (SeqList sl, Iterator it);

#ifndef __WITHOUT_KEY
Element find (const SeqList sl,const Key k);
int compare (const Key k1,const Key k2);
SeqList insertInOrder (SeqList sl, Element e);
SeqList delete (SeqList sl, Element e);
#endif

//Following functions should be overridden by the user if key and elements are changed
//default versions are supplied in stack.c
//override by defining __COMPARE and __FREEELEMENT in complining stack.c

void freeElement (Element e);   //user needs to define this
#endif
