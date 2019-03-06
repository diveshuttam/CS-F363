#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*int main(void){
	hashTable ht = newHashTable(100);
	ht = insert("Rahul",1,ht);
	ht = insert("Divesh",3,ht);
	char* map[] = {"1","Rahul","2","Divesh"};
	debug_msg("%d\n", findHT("Divesh",ht,map,4));
	return 0;
}*/

hashTable newHashTable(int size){
	hashTable* ht = (hashTable*)malloc(sizeof(hashTable));
	ht->array = (SeqList*)malloc(sizeof(SeqList)*size);
	for(int i=0;i<size;i++){
		ht->array[i] = newList();
	}
	ht->size = size;
	return *ht;
}

int hash(char *str,int size,int b,int a)
{
    unsigned long hash = b;
    int c;

    while (c = *str++)
        hash = ((hash << a) + hash) + c; /* hash * 33 + c */

    return hash % size;
}

Element createElement(int data){
	Element e=malloc(sizeof(Element));
	e->k=malloc(sizeof(Key));
	e->k->data=data;
	return e;
	
}

void printElement(Element e){
	debug_msg("%d\n", e->k->data);
}

/*
char *map[]
0-> "program"
1-> "abc"
*/

int findHT(char* str,hashTable ht,char* map[],int n){
	int hash_val = hash(str,ht.size,5381,5);
	Iterator it = getIterator(ht.array[hash_val]);
	int index;
	while(hasNext(it)){
		index = getNext(it)->k->data;
		if(strcmp(map[index],str) == 0){
			return index;
		}
		it =next(it);
	}
	return -1;
}

hashTable insert(char* str,int index,hashTable ht){
	int hash_val = hash(str,ht.size,5381,5);
	Element e=createElement(index);
	if(ht.array[hash_val] == NULL){
		ht.array[hash_val] = newList();
		ht.array[hash_val] = insertAtEnd(ht.array[hash_val],e);
	}else{
		ht.array[hash_val] = insertAtEnd(ht.array[hash_val],e);

	}
	return ht;
}


