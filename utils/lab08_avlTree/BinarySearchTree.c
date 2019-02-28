#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "TreeDefinition.h"

#define __STACKELEMENT
typedef BinarySearchTree StackElement;
#include "includes/Stack.h"
#include <stdlib.h>

//greater than right
//LESSTHAN to left

typedef enum UPDT_TYPE{ADD, DEL, NONE} UPDT_TYPE;

typedef struct Stack *PathStack;

int max(int a, int b)
{
	return (a>b)?a:b;
}
int getBalance(BinarySearchTree bst)
{
	return bst->balance;
}

void setBalance(BinarySearchTree bst,int balance)
{
	bst->balance=balance;
}

//complexity o(pathlength) only go to the heavy side
int getHeight(BinarySearchTree bst)
{
	int height=0;
	BinarySearchTree cur=bst;
	while(!isEmpty(cur))
	{
		++height;
		if(getBalance(cur)==-1)
		{
			cur=getLeft(cur);
		}	
		else
		{
			cur=getRight(cur);
		}
	}
	return height;
}

/* assuming difference pass none to update all correctly*/
//complexity o(pathLength)
void updateBalance(PathStack p, UPDT_TYPE t)
{
	BinarySearchTree E;

	if(t==NONE)
	{
		while((E=top(p))!=NULL)//while stack is not empty
		{
			setBalance(E,max(getHeight(getLeft(E)),getHeight(getRight(E)))+1);
			p=pop(p);
		}
	}
	else if(t==ADD || t==DEL)
	{
		//to be implemented
	}
}

#ifndef __COMPARE
#define __COMPARE
COMP_RET compare(Key k1, Key k2)
{
	if(k1<k2)
		return LESSTHAN;
	else if(k1>k2)
		return GREATERTHAN;
	else
		return EQUALTO;
}
#endif

PathStack traverseStack(BinarySearchTree bst, Key k)
{
	PathStack p=newStack();
	COMP_RET ret;
	BinarySearchTree cur=bst;
	while(!isEmpty(cur))
	{
		p=push(p,cur);
		ret=compare(k,getRoot(cur)->k);
		if(ret==GREATERTHAN)
			cur=getRight(cur);
		else if(ret==LESSTHAN)
			cur=getLeft(cur);
		else if(ret==EQUALTO)
			break;
	}
	  return p;
}

Element find(BinarySearchTree bst, Key k)
{
  //empty case
  if(isEmpty(bst))
    return NULL;//NOT_FOUND
  Element r=getRoot(bst);  
  //base case (root)
  if(compare(r->k,k)==EQUALTO)
    return r;
  //case right
  else if(compare(k, r->k)==GREATERTHAN)
    return find(getRight(bst), k);
  //case left
  else
    return find(getLeft(bst), k);
}

//if the Key is already there then update
BinarySearchTree add(BinarySearchTree bst, Element e)
{
  //case empty
	BinarySearchTree e1=mkBTNode(e);
  if(isEmpty(bst))
  	return e1;
	
	PathStack p=traverseStack(bst, e->k);
  
  BinarySearchTree r=top(p);
  
  //case equal --> update
  if(compare(e->k,getRoot(r)->k)==EQUALTO)
  		setRoot(r,e);
  //case right
  else if(compare(e->k,getRoot(r)->k)==GREATERTHAN)
      setRight(r,e1);
  //case left
  else
  		setLeft(r,e1);
	push(p,e1);
	//updateBalance(p, NONE);
	//updateBalance(p, DEL);
	return bst;
}

//returns successor
PathStack inOrderSuccessor(BinarySearchTree bst,Key k)
{
  PathStack p=traverseStack(bst, k);
	BinarySearchTree E,E1,cur,curparent;
	E=top(p);
	//if not found
	if(getRoot(E)->k!=k)
	{
		return NULL;
	}
  //if has a right sub tree, then go left left
  if(!isEmpty(getRight(E)))
  {
    cur=getRight(E);
    while(!isEmpty(cur))
    {
      p=push(p,cur);
      cur=getLeft(cur);
    }
		return p;
  }
  //find the first parent who has this as a left subtree
  else
  {
    cur=top(p);
    p=pop(p);
    curparent=top(p);
    while(curparent!=NULL)//stack is not empty
    {
      if(getLeft(curparent)==cur)
        break;
      cur=top(p);
      p=pop(p);
      curparent=top(p);
    }
    if(curparent==NULL)
      return NULL;
    else
			return p;
	}
}

BinarySearchTree delete(BinarySearchTree bst, Key k)
{
	PathStack p=traverseStack(bst, k);
	BinarySearchTree E;
	
	if(top(p)!=NULL && getRoot(top(p))->k==k){//path element is found
	  E=top(p);
	  
	  //swap if none of the child is empty
	  if(!isEmpty(getRight(E)) && !isEmpty(getLeft(E)))
	  {
	    PathStack pios=inOrderSuccessor(bst,k);
	    //swap successor and self
	    Element a=getRoot(top(p));
	    setRoot(top(p),getRoot(top(pios)));
	    setRoot(top(pios),a);
	    //change p to pios	
	    p=pios;
	  }
		E=top(p);
  
    //deletes actually here
	  //right is empty
	  if(isEmpty(getRight(E)))
	  {
	    p=pop(p);
			if(top(p)==NULL)
			{
				return getLeft(E);
			}
	    BinarySearchTree parent=top(p);
	    if(E==getRight(parent))
	    {
	      setRight(parent,getLeft(E));
	    }
	    else
	    {
	      setLeft(parent,getLeft(E));
	    }
	  }
	  //left is empty
	  else if(isEmpty(getLeft(E)))
	  {
		  //override parent's right/left with my non empty child
		  p=pop(p);
			if(top(p)==NULL)
				return getRight(E);
	    BinarySearchTree parent=top(p);
	    if(E==getRight(parent))
	    {
	      setRight(parent,getRight(E));
	    }
	    else
	    {
	      setLeft(parent,getRight(E));
	    }
	  }
	}
	return bst;
}
