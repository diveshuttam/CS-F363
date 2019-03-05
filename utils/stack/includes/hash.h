#include "SeqList.h"

typedef struct Node
{
  Element e;
  struct Node *next;
} *Node;

hashTable newHashTable(int size);
int hash(char *str,int size,int b,int a);
hashTable insert(char* str,int index,hashTable ht);
int findHT(char* str,hashTable ht,char* map[],int n);