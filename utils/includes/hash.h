#ifndef __HASHT
#define __HASHT
#include "debug.h"
typedef struct hashTable *hashTable;

hashTable newHashTable(const int size,const int a,const int b);
void insert(const char* str,const int index,hashTable ht);
int findHT(const char* str,const hashTable ht);
#endif