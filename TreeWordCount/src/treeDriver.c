/**************************************************************************
 File name:  treeDriver.c
 Author:     Ellysia Li
 Date:		 	 Nov 10, 2019
 Class:		   CS300
 Assignment: Trees
 Purpose:    Testing of a binary search tree struct
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

int main ()
{
	TreeNodePtr psRoot;

	trLoadErrorMessages ();

	trCreate (&psRoot);
	puts ("Created Tree");
	if (psRoot->count != 0 || psRoot->psLeft != NULL || psRoot->psRight != NULL)
	{
		puts ("Error: trCreate invalid");
	}
	if (!trIsEmpty(psRoot))
	{
		puts ("Error: Initiated tree is NOT empty");
	}

	trInsert (&psRoot, "First", 1);
	if (psRoot->count != 1 || psRoot->psLeft != NULL || psRoot->psRight != NULL)
	{
		puts ("Error: trInsert invalid");
	}
	printf ("First node added has key: %s\n", psRoot->szWord);

	trTerminate (&psRoot);
	if (psRoot != NULL)
	{
		puts ("Error: trTerminate invalid");
	}

	trCreate (&psRoot);
	trInsert (&psRoot, "B", 1);
	trInsert (&psRoot, "A", 1);
	trInsert (&psRoot, "C", 1);

	printf ("Root node added has key: %s\n", psRoot->szWord);
	printf ("Root's left child has key: %s\n", psRoot->psLeft->szWord);
	printf ("Root's right child has key: %s\n", psRoot->psRight->szWord);

	trInsert (&psRoot, "Cd", 1);
	printf ("C's right child has key: %s\n", psRoot->psRight->psRight->szWord);
	trInsert (&psRoot, "Ab", 1);
	printf ("A's right child has key: %s\n", psRoot->psLeft->psRight->szWord);
	trTerminate (&psRoot);

	if (psRoot != NULL)
	{
		puts ("Error: trTerminate invalid");
	}

	return 0;
}
