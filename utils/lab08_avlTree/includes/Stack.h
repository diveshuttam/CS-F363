#ifndef __STACK_H
#define __STACK_H

#ifndef __STACK
#define __STACK
typedef struct Stack *Stack;
#endif

#ifndef __KEY
#define __KEY
typedef int Key;
#endif

#ifndef __STACKELEMENT
#define __STACKELEMENT
typedef struct BinaryTree *StackElement;
#endif

Stack newStack ();
Stack pop (Stack s);
Stack push (Stack s, StackElement e);
StackElement top (Stack s);
Stack clearStack (Stack s);
#endif
