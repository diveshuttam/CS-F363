#ifndef __HASHT
#define __HASHT
#include "SeqList.h"

typedef struct Node
{
  Element e;
  struct Node *next;
} *Node;

typedef struct hashTable
{	
	int size;
	SeqList* array;
}hashTable;
hashTable* newHashTable(int size);
int hash(char *str,int size,int b,int a);
void insert(char* str,int index,hashTable* ht);
int findHT(char* str,hashTable *ht,char* map[],int n);
#endif