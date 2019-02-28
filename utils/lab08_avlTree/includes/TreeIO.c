#include "TreeIO.h"
#include<stdio.h>
#include<stdlib.h>

void
printTree (BinarySearchTree N){
    if(isEmpty(N))
        return;
    printTree(getLeft(N));
    printf("%d\n",getRoot(N)->k);
    printTree(getRight(N));

}

Element getElement(Key k)
{
    Element e=malloc(sizeof(struct Element));
    e->k=k;
    return e;
}