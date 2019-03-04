#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "SeqList.h"

char* getKey(Element e){
	char *k=e->k;
	return k;
}

int getData(Element e){
	int *d=e->d;
	return *d;
}

hashTable newHashTable(int size, int significant_bits, int salt){
	hashTable ht;
	ht.b=salt;
	ht.a=significant_bits;
	ht.array = (SeqList*)malloc(sizeof(SeqList)*(size+1));
	for(int i=0;i<size;i++){
		ht.array[i] = newList();
	}
	ht.size = size;
	return ht;
}

int hash(char *str, hashTable ht)
{
    unsigned long hash = ht.b;
    int c;

    while (c = *str++)
        hash = ((hash << ht.a) + hash) + c; /* hash * 33 + c */
	hash=(hash % ht.size);
    return hash;
}

Element createElement(int data, char *key){
	Element e=malloc(sizeof(struct Element));
	e->d=malloc(sizeof(int));
	int* l=e->d;
	*l=data;
	e->k=malloc(sizeof(char*)*(strlen(key)+1));
	char *buf=(char*)(e->k);
	strcpy(buf,key);
	return e;
}

void printElement(Element e){
	printf("%d : %s \n", *(int *)(e->d), (char*)(e->k));
}

/*
char *map[]
0-> "program"
1-> "abc"
*/

int findHT(char* str,hashTable ht){
	if(str==NULL){
		return -1;
	}
	int hash_val = hash(str,ht);
	Iterator it = getIterator(ht.array[hash_val]);
	while(hasNext(it)){
		char* key = getKey(getNext(it));
		int data = getData(getNext(it));
		if(strcmp(key,str) == 0){
			return data;
		}
		it =next(it);
	}
	return -1;
}

void insert(char* str,int index,hashTable ht){
	if(str!=NULL){
		printf("inserting element %s\n", str);
		int hash_val = hash(str,ht);
		Element e=createElement(index, str);
		if(ht.array[hash_val] == NULL){
			printf("error in hash.c");
			exit(0);
		}else{
			ht.array[hash_val] = insertAtEnd(ht.array[hash_val],e);
		}
	}
	else{
		printf("str passed null to insert\n");
	}
	return ;
}


