#ifndef __HASHT
#define __HASHT
#include "debug.h"
typedef struct hashTable *hashTable;

hashTable newHashTable(const int size,const int a,const int b);
void insertInt(const char* str,const int index,hashTable ht);
int findHTInt(const char* str,const hashTable ht);

void insert(const char* str,const void* entry,hashTable ht);
void* findHT(const char* str,const hashTable ht);
#endif