#ifndef __HASHT
#define __HASHT

typedef struct hashTable *hashTable;

hashTable newHashTable(int size, int a, int b);
void insert(char* str,int index,hashTable ht);
int findHT(char* str,hashTable ht);
#endif