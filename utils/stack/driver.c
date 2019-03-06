//the main function for the Stack program is contained in this file
#include <signal.h>
#include <stdlib.h>
#include "includes/StackIO.h"
#include "Stack.h"
#include <stdio.h>

Stack s;

//handling the signals for clearing and exit
void
sigint_handler (int dummy)
{
  debug_msg ("\nYou chose to exit!\n");
  exit (0);
}

void
sigquit_handler (int dummy)
{
  debug_msg ("\nClearing the Stack now\n");
  s = clearStack (s);
  debug_msg ("Stack List has been cleared\n");
}

//end of signal handling

int
main ()
{
  //handle ctrl+c in driver itself
  signal (SIGQUIT, sigquit_handler);
  signal (SIGINT, sigint_handler);
  int choice;
  s = newStack ();
  //printning menu to stderr as well as the input statements
  //printing ouput of the functions to stdout
  setRedirection ();
  do
    {
      if (checkRedirect)
        clrerr ();
      fprintf (stderr, "\n-----------------------------------\n\
Main Menu:\n\
 1.push()\n\
 2.pop()\n\
 3.top()\n\
 4.random push()\n\
 5.multiple pop()\n\
Please enter a choice[0-5]\n\
[Ctrl+\\ to clear the Stack, Ctrl+C to exit (asynchronously)]\n\
-----------------------------------\n");

      scanf ("%d", &choice);
      Key k;
      Element e;
      int noOfElements;
      switch (choice)
        {
        case 1:
          e = askElement ();
          s = push (s, e);
          break;
        case 2:
          s = pop (s);
          break;
        case 3:
          e = top (s);
          debug_msg ("the top of the stack is: ");
          printElement (e);
          break;
        case 4:
          fprintf (stderr, "enter the no of elements to push");
          scanf ("%d", &noOfElements);
          debug_msg ("inserting elements\n");
          s = randomElements (s, noOfElements, push);
          debug_msg ("Done");
          break;
        case 5:
          fprintf (stderr, "enter the no of elements to pop");
          scanf ("%d", &noOfElements);
          debug_msg ("poping elements\n");
          for (int i = 0; i < noOfElements; i++)
            {
              s = pop (s);
            }
          debug_msg ("Done");
          break;
        default:
          fprintf (stderr, "invalid choice");
        }
    }
  while (1);
  return 0;
}
