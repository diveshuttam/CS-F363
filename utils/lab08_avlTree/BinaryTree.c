#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "BinaryTree.h"
#include "TreeDefinition.h"
typedef struct BinaryTree *BinaryTree;

BinaryTree
mkBTNode (Element e)
{
  BinaryTree n = malloc (sizeof (struct BinaryTree));
  n=setRoot(n,e);
  n=setLeft(n,NULL);
  n=setRight(n,NULL);
  n->balance=0;
  return n;
}

BinaryTree createTree()
{
  return NULL;
}

BinaryTree compose(Element e, BinaryTree lt, BinaryTree rt)
{
  BinaryTree newT = mkBTNode(e);
  newT=setLeft(newT,lt);
  newT=setRight(newT,rt);
  return newT;
}

bool isEmpty (BinaryTree t)
{
  return (t==NULL)?true:false;
}

Element getRoot(BinaryTree t)
{
  return t->rootVal;
}

BinaryTree setRoot(BinaryTree t, Element e)
{
  t->rootVal=e;
  return t;
}

BinaryTree getLeft(BinaryTree t)
{
  return t->left;
}

BinaryTree getRight(BinaryTree t)
{
  return t->right;
}

BinaryTree setLeft(BinaryTree t, BinaryTree lt)
{
  t->left=lt;
  return t;
}

BinaryTree setRight(BinaryTree t, BinaryTree rt)
{
  t->right=rt;
  return t;
}