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
	int valueBuffer;
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

	trPrintInOrder (psRoot);

	if (!trInsert (&psRoot, "Cd", 1))
	{
		puts ("Returned false in trInsert successfully");
	}

	trUpdate (psRoot, "B", 2);
	printf ("B has count of: %d\n", psRoot->count);
	trUpdate (psRoot, "A", 3);
	printf ("A has count of: %d\n", psRoot->psLeft->count);
	trUpdate (psRoot, "C", 4);
	printf ("C has count of: %d\n", psRoot->psRight->count);
	trUpdate (psRoot, "Cd", 5);
	printf ("Cd has count of: %d\n", psRoot->psRight->psRight->count);
	trUpdate (psRoot, "Ab", 6);
	printf ("Ab has count of: %d\n", psRoot->psLeft->psRight->count);

	if (!trUpdate (psRoot, "XX", 1))
	{
		puts ("Returned false in trUpdate successfully");
	}

	trFind (psRoot, "B", &valueBuffer);
	printf ("B has a found count of: %d\n", valueBuffer);
	trFind (psRoot, "A", &valueBuffer);
	printf ("A has a found count of: %d\n", valueBuffer);
	trFind (psRoot, "C", &valueBuffer);
	printf ("C has a found count of: %d\n", valueBuffer);
	trFind (psRoot, "Cd", &valueBuffer);
	printf ("Cd has a found count of: %d\n", valueBuffer);
	trFind (psRoot, "Ab", &valueBuffer);
	printf ("Ab has a found count of: %d\n", valueBuffer);

	if (!trFind (psRoot, "1", &valueBuffer))
	{
		puts ("Returned false in trFind successfully");
	}

	trTerminate (&psRoot);

	if (psRoot != NULL)
	{
		puts ("Error: trTerminate invalid");
	}

	return 0;
}
