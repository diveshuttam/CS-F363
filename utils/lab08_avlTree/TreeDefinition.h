#include "BinaryTree.h"

#ifndef __BINARY_TREE
#define __BINARY_TREE
typedef struct BinaryTree *BinaryTree;

struct BinaryTree
{
  Element rootVal;
  BinaryTree right;
  BinaryTree left;
  int balance:2;
};
#endif