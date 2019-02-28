#include<stdio.h>
#include"BinarySearchTree.h"
#include<stdlib.h>
#include"includes/TreeIO.h"

BinarySearchTree bst;

BinarySearchTree
populateTree (BinarySearchTree bst)
{
  int i = 0;
  int max = 100000;

  while (i < max)
    {
      i++;
      int k=150 + (random () % 21);
      Element E=getElement(k);
      bst = add (bst, E);
    }
  return bst;
}

int
main ()
{
  int ch, val;
  do
    {
      printf ("Main Menu\n"
              "1. ADD a NODE\n"
              "2. Print tree\n"
              "3. find a node\n"
              "4. populate tree with random [150-170]\n"
              "5. delete a node\n"
              "Enter your choice:\t");
      scanf ("%d", &ch);
      switch (ch)
        {
        case 1:
          printf ("Enter the value:");
          scanf ("%d", &val);
          Element E=getElement(val);
          bst = add (bst, E);
          break;
        case 2:
          printTree (bst);
          break;
        case 3:
          printf ("Enter the value:");
          scanf ("%d", &val);
          if (find (bst, val) != NULL)
            printf ("value found\n");
          else
            printf ("value not found\n");
          break;
        case 4:
          //add 10000 random no. between 150 and 170
          bst = populateTree (bst);
          break;
        case 5:
          printf ("Enter the value:");
          scanf ("%d", &val);
          bst = delete(bst, val);
          break;
        default:
          exit (0);
        }
    }
  while (1);
}