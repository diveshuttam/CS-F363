//Authro: Divesh Uttamchandani
//2016A7PS0045P

#ifndef __SEQLIST_H
#define __SEQLIST_H

#include <stdbool.h>

#define GREATERTHAN 1
#define LESSTHAN -1
#define EQUALTO 0

#ifndef __KEY
#define __KEY
typedef struct Key
{
  int data;
} *Key;
#endif

#ifndef __ELEMENT
#define __ELEMENT
typedef struct Element
{
  Key k;
} *Element;
#endif

#ifndef __SEQLIST
#define __SEQLIST
typedef struct SeqList *SeqList;
#endif

#ifndef __ITERATOR
#define __ITERATOR
typedef struct Iterator *Iterator;
#endif

SeqList newList ();
SeqList clearList (SeqList sl);
SeqList insertInOrder (SeqList sl, Element e);
SeqList insertAtFront (SeqList sl, Element e);
SeqList insertAtEnd (SeqList sl, Element e);
SeqList delete (SeqList sl, Element e);
SeqList deleteAtFront (SeqList sl);
Element find (SeqList sl, Key k);
Iterator getIterator (SeqList sl);
Iterator next (Iterator it);
Element getNext (Iterator it);
bool hasNext (Iterator it);
SeqList insertBefore (SeqList sl, Iterator it, Element E);
SeqList deleteAfter (SeqList sl, Iterator it);

//Following functions should be overridden by the user if key and elements are changed
//default versions are supplied in stack.c
//override by defining __COMPARE and __FREEELEMENT in complining stack.c
int compare (Key k1, Key k2);
void freeElement (Element e);   //user needs to define this
#endif
