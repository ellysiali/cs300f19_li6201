/**************************************************************************
 File name:  pqueuedriver.c
 Author:     Ellysia Li
 Date:		   Oct 15, 2019
 Class:		   CS300
 Assignment: Priority Queue Implementation
 Purpose:    Test driver for a priority queue data structure
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/pqueue.h"
#include "../../GenericDynamicList/include/list.h"

#define MAX_BUFFER_CHARS 100
#define EVEN 2
#define DOUBLE 2
#define CHAR_START 65
#define CHAR_END 90
#define LONG_LIST_LENGTH 1000
#define VERY_LONG_LIST_LENGTH 1000000
#define PRIORITY 7
#define PRIORITY_ADD 100
#define PRIORITY_SUB -50

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

 Returned:	 	none

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
	char i, charBuffer;
	int j, intBuffer, priorityBuffer;
	float k, floatBuffer;

	puts ("Start Driver\n");

	// Validate the initiated queue (after pqueueCreate)

	pqueueCreate (&sTheQueue);
	assert (0 == pqueueSize (&sTheQueue), "Initialized queue size is 0",
			"Initialized queue size is NOT 0");
	assert (pqueueIsEmpty (&sTheQueue), "Initialized queue is empty\n",
			"Initialized queue is NOT empty\n");

	// Create a very long queue and validate when terminated (repeat twice)

	for (j = 0; j < VERY_LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), j);
	}
	pqueueTerminate (&sTheQueue);
	assert (0 == pqueueSize (&sTheQueue),
			"Terminated queue (from nonempty) size is 0",
			"Terminated queue (from nonempty) size is NOT 0");
	assert (pqueueIsEmpty (&sTheQueue),
			"Terminated queue (from nonempty) is empty\n",
			"Terminated queue (from nonempty) is NOT empty\n");

	for (j = 0; j < VERY_LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), j);
	}
	pqueueTerminate (&sTheQueue);

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
			assert (!pqueueIsEmpty (&sTheQueue), "Validated queue is not empty",
					"Could not validate (queue is empty)");
		}
		pqueuePeek (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
		if (i != charBuffer)
		{
			assert (i == charBuffer, "Validated first (peeked) element is correct",
					"Could not validate (first (peeked) element is NOT correct)");
		}
		if (CHAR_END - i != priorityBuffer)
		{
			assert (i == charBuffer, "Validated first (peeked) priority is correct",
					"Could not validate (first (peeked) priority is NOT correct)");
		}
	}
	success ("Added elements to the beginning of the queue and validated "
			"appropriately\n");

	// Remove chars using pqueueDequeue and validate appropriately

	for (i = CHAR_END; CHAR_START <= i; i--)
	{
		pqueueDequeue (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
		if (i != charBuffer)
		{
			assert (i == charBuffer, "Validated removed element value is correct",
					"Could not validate (removed element value is NOT correct)");
		}
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
	success ("Removed elements from the queue and validated appropriately");

	// Validate completely deleted queue

	assert (0 == pqueueSize (&sTheQueue), "Fully deleted queue size is 0",
			"Fully deleted queue size is NOT 0");
	assert (pqueueIsEmpty (&sTheQueue), "Fully deleted queue is empty\n",
			"Fully deleted queue is NOT empty\n");

	pqueueTerminate (&sTheQueue);

	// Create a queue using all the same priorities and validate order

	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), PRIORITY);
	}
	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueDequeue (&sTheQueue, &intBuffer, sizeof (int), &priorityBuffer);
		if (j != intBuffer)
		{
			assert (j == intBuffer, "Validated removed element value is correct",
					"Could not validate (removed element value is NOT correct)");
		}
		if (PRIORITY != priorityBuffer)
		{
			assert (0 == priorityBuffer,
					"Validated removed priority is correct",
					"Could not validate (removed priority is NOT correct)");
		}
	}
	success ("Added elements with the same priority and validated order");

	// Create a long queue, adding to the middle/end using pqueueEnqueue
	// (some with the same priority) and validate appropriately

	pqueueCreate (&sTheQueue);

	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), j);
	}
	for (k = 0; k < LONG_LIST_LENGTH; k = k + 1)
	{
		pqueueEnqueue (&sTheQueue, &k, sizeof (float), (int) k);
	}

	for (j = 0; j < DOUBLE * LONG_LIST_LENGTH; j++)
	{
		if (0 == j % EVEN)
		{
			pqueueDequeue (&sTheQueue, &intBuffer, sizeof (int), &priorityBuffer);
			if (j / DOUBLE != intBuffer)
			{
				assert (j / DOUBLE == intBuffer,
						"Validated removed element value is correct",
						"Could not validate (removed element value is NOT correct)");
			}
			if (j / DOUBLE != priorityBuffer)
			{
				assert (j / DOUBLE == priorityBuffer,
						"Validated removed priority is correct",
						"Could not validate (removed priority is NOT correct)");
			}
		}
		else
		{
			pqueueDequeue (&sTheQueue, &floatBuffer, sizeof (float), &priorityBuffer);
			if ((float) (j - 1) / DOUBLE != floatBuffer)
			{
				assert ((float) (j - 1) / DOUBLE == floatBuffer,
						"Validated removed element value is correct",
						"Could not validate (removed element value is NOT correct)");
			}
			if ((j - 1) / DOUBLE != priorityBuffer)
			{
				assert ((j - 1) / DOUBLE == priorityBuffer,
						"Validated removed priority is correct",
						"Could not validate (removed priority is NOT correct)");
			}
		}
		if (DOUBLE * LONG_LIST_LENGTH - j - 1 != pqueueSize (&sTheQueue))
		{
			assert (DOUBLE * LONG_LIST_LENGTH - j - 1 == pqueueSize (&sTheQueue),
					"Validated deleted queue size is correct",
					"Could not validate (deleted queue size is NOT correct)");
		}
	}

	success ("Added elements to the middle/end of the queue and validated "
			"order\n");

	// Validate pqueueChangePriority on a queue

	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), j);
	}

	pqueueChangePriority (&sTheQueue, PRIORITY_ADD);

	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueDequeue (&sTheQueue, &intBuffer, sizeof (int), &priorityBuffer);
		if (j + PRIORITY_ADD != priorityBuffer)
		{
			assert (j + PRIORITY_ADD == priorityBuffer,
					"Validated updated (added) priority is correct",
					"Could not validate (updated [added] priority is NOT correct)");
		}
	}
	success ("Changed priorities (when adding) is correct");
	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueEnqueue (&sTheQueue, &j, sizeof (int), j);
	}

	pqueueChangePriority (&sTheQueue, PRIORITY_ADD);
	pqueueChangePriority (&sTheQueue, PRIORITY_SUB);

	for (j = 0; j < LONG_LIST_LENGTH; j++)
	{
		pqueueDequeue (&sTheQueue, &intBuffer, sizeof (int), &priorityBuffer);
		if (j + PRIORITY_ADD + PRIORITY_SUB != priorityBuffer)
		{
			assert (j + PRIORITY_ADD + PRIORITY_SUB == priorityBuffer,
					"Validated updated (subtracted) priority is correct",
					"Could not validate (updated [subtracted] priority is NOT correct)");
		}
	}
	success ("Changed priorities (when subtracting) is correct\n");

	pqueueTerminate (&sTheQueue);

	puts ("End Driver");
	return EXIT_SUCCESS;
}
