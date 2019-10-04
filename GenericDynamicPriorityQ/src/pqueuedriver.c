/**************************************************************************
 File name:  pqueuedriver.c
 Author:     Ellysia Li
 Date:		   Oct 3, 2019
 Class:		   CS300
 Assignment: Priority Queue Implementation
 Purpose:    Test driver for a priority queue data structure
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/pqueue.h"
#include "../../GenericDynamicList/include/list.h"

#define MAX_BUFFER_CHARS 100
#define CHAR_START 65
#define CHAR_END 90
#define LONG_LIST_LENGTH = 100000;

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success (char *pszStr)
{
	printf ("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message and exit the program

 Parameters:	pszStr - the message to print

 Returned:	 	none#define DELETE_MID 2

 ****************************************************************************/
static void failure (char *pszStr)
{
	printf ("FAILURE: %s\n", pszStr);
	exit (EXIT_FAILURE);
}

/****************************************************************************
 Function: 	 		assert

 Description: 	if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	  failure

 Parameters:		szStr - the message to print

 Returned:	 		none
 ****************************************************************************/
static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	PriorityQueue sTheQueue;
	int priorityBuffer;
	char i, charBuffer, aszSuccess[MAX_BUFFER_CHARS],
	aszFailure[MAX_BUFFER_CHARS];
	puts ("Start Driver");

	// Validate the initiated queue (after pqueueCreate)

	pqueueCreate (&sTheQueue);
	assert (0 == pqueueSize (&sTheQueue), "Initialized queue size is 0",
			"Initialized queue size is NOT 0");
	assert (pqueueIsEmpty (&sTheQueue), "Initialized queue is empty",
			"Initialized queue is NOT empty");

	puts ("");

	// Add chars to the beginning of the queue using pqueueEnqueue and validate
	// appropriately

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		pqueueEnqueue (&sTheQueue, &i, sizeof (char), CHAR_END - i);
		if (i - CHAR_START + 1 != pqueueSize (&sTheQueue))
		{
			assert (i - CHAR_START + 1 == pqueueSize (&sTheQueue),
					"Validated queue size is correct",
					"Could not validate (queue size is NOT correct)");
		}
		if (pqueueIsEmpty (&sTheQueue))
		{
			assert (!pqueueIsEmpty (&sTheQueue),
					"Validated queue is not empty",
					"Could not validate (queue is empty)");
		}
		pqueuePeek (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
		if (i != charBuffer)
		{
			assert (i == charBuffer, "Validated first (peeked) element is correct",
					"Could not validate (first (peeked) element is NOT correct)");
		}
	}

	// Remove chars using pqueueDequeue and validate appropriately

	for (i = CHAR_END; CHAR_START <= i; i--)
	{
		pqueueDequeue (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
		sprintf (aszSuccess, "Removed element is %c", i);
		sprintf (aszFailure, "Removed element is NOT %c", i);
		assert (i == charBuffer, aszSuccess, aszFailure);
		if (CHAR_END - i != priorityBuffer)
		{
			assert (CHAR_END - i == priorityBuffer,
					"Validated removed priority is correct",
					"Could not validate (removed priority is NOT correct)");
		}
		if (i - CHAR_START != pqueueSize (&sTheQueue))
		{
			assert (i - CHAR_START + 1 == pqueueSize (&sTheQueue),
					"Validated deleted queue size is correct",
					"Could not validate (deleted queue size is NOT correct)");
		}
	}

	puts ("");

	// Validate completely deleted queue

	assert (0 == pqueueSize (&sTheQueue), "Fully deleted queue size is 0",
			"Fully deleted queue size is NOT 0");
	assert (pqueueIsEmpty (&sTheQueue), "Fully deleted queue is empty",
			"Fully deleted queue is NOT empty");

	pqueueTerminate (&sTheQueue);

	/*
	 * TO DO:
	 * - Terminate the queue when non-empty
	 * - Add a bunch of ints and make sure to queue in the middle and end
	 *   (mess around with the priorities)
	 * - Implement pqueueChangePriority
	 */

	puts ("End Driver");
	return EXIT_SUCCESS;
}
