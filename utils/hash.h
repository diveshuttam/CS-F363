#ifndef __HASHT
#define __HASHT

#include "SeqList.h"

typedef struct hashTable
{	
	int size;
  int a;
  int b;
	SeqList* array;
}hashTable;

hashTable newHashTable(int size, int a, int b);
void insert(char* str,int index,hashTable ht);
int findHT(char* str,hashTable ht);
#endif