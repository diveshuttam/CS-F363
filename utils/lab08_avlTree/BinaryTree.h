#ifndef __BINARYTREE_H
#define __BINARYTREE_H
#include<stdbool.h>

#ifndef __KEY
#define __KEY
typedef int Key;
#endif

#ifndef __BINARYTREE
#define __BINARYTREE
typedef struct BinaryTree *BinaryTree;
#endif


#ifndef __ELEMENT
#define __ELEMENT
typedef struct Element{
    Key k;
}*Element;
#endif

//functions declaration start here
bool isEmpty (BinaryTree t);
Element getRoot(BinaryTree t);
BinaryTree createTree ();
BinaryTree mkBTNode(Element e);
BinaryTree setRoot(BinaryTree t, Element e);
BinaryTree getLeft(BinaryTree t);
BinaryTree getRight(BinaryTree t);
BinaryTree setLeft(BinaryTree t, BinaryTree lt);
BinaryTree setRight(BinaryTree t, BinaryTree rt);
BinaryTree compose(Element e, BinaryTree lt, BinaryTree right);
#endif