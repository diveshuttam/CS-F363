#ifndef __ELEMENT_H
#define __ELEMENT_H
typedef char *Key;
typedef int *Data;
typedef struct Element *Element;

struct Element
{
  Key k;
  Data d;
};
#endif