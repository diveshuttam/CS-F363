#ifndef __BST_H
#define __BST_H

#ifndef __KEY
#define __KEY
typedef int Key;
#endif

#ifndef __ELEMENT
#define __ELEMENT
typedef struct Element{
    Key k;
}*Element;
#endif

#ifndef __BINARYSEARCHTREE 
#define __BINARYSEARCHTREE
typedef struct BinaryTree *BinarySearchTree;
#endif

typedef enum COMP_RET
{ LESSTHAN, GREATERTHAN, EQUALTO } COMP_RET;

BinarySearchTree add (BinarySearchTree root, Element e);
Element find (BinarySearchTree root, Key k);
BinarySearchTree delete (BinarySearchTree root, Key k);
COMP_RET compare (Key k1, Key k2);
#endif