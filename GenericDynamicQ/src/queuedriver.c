/**************************************************************************
 File name:  queuedriver.c
 Author:     Ellysia Li
 Date:		   Oct 20, 2019
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    Testing of a Generic Queue backed by a existing Priority
 	 	 	 	 	 	 Queue
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

#define LONG_QUEUE_LENGTH 1000
#define VERY_LONG_QUEUE_LENGTH 1000000
#define CHAR_START 65
#define CHAR_END 90
#define EVEN 2

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

 Description: test all the functionality of the general queue

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	Queue sTheQueue;
	char i, charBuffer;
	int j, intBuffer;
	float floatBuffer;

	puts ("Driver Start\n");
	queueLoadErrorMessages ();

	// Validate the initiated queue (after queueCreate)

	queueCreate (&sTheQueue);
	assert (0 == queueSize (&sTheQueue), "Initialized queue size is 0",
			"Initialized queue size is NOT 0");
	assert (queueIsEmpty (&sTheQueue), "Initialized queue is empty\n",
			"Initialized queue is NOT empty\n");

	// Create a very long queue and validate when terminated (repeat twice)

	for (j = 0; VERY_LONG_QUEUE_LENGTH > j; j++)
	{
		queueEnqueue (&sTheQueue, &j, sizeof (int));
	}

	queueTerminate (&sTheQueue);

	assert (0 == queueSize (&sTheQueue),
			"Terminated queue (from nonempty) size is 0",
			"Terminated queue (from nonempty) size is NOT 0");
	assert (queueIsEmpty (&sTheQueue),
			"Terminated queue (from nonempty) is empty\n",
			"Terminated queue (from nonempty) is NOT empty\n");

	queueCreate (&sTheQueue);

	for (j = 0; VERY_LONG_QUEUE_LENGTH > j; j++)
	{
		queueEnqueue (&sTheQueue, &j, sizeof (int));
	}
	queueTerminate (&sTheQueue);

	// queueEnqueue and queueDequeue chars and validate appropriately

	queueCreate (&sTheQueue);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		queueEnqueue (&sTheQueue, &i, sizeof (char));
		if (i - CHAR_START + 1 != queueSize (&sTheQueue))
		{
			assert (i - CHAR_START + 1 == queueSize (&sTheQueue),
					"Validated queue size is correct",
					"Could not validate (queue size is NOT correct)");
		}
		if (queueIsEmpty (&sTheQueue))
		{
			assert (!queueIsEmpty (&sTheQueue), "Validated queue is not empty",
					"Could not validate (queue is empty)");
		}
		queuePeek (&sTheQueue, &charBuffer, sizeof(char));
		if (CHAR_START != charBuffer)
		{
			assert (i == charBuffer, "Validated first (peeked) element is correct",
					"Could not validate (first (peeked) element is NOT correct)");
		}
	}

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		queueDequeue (&sTheQueue, &charBuffer, sizeof (char));
		if (i != charBuffer)
		{
			assert (i == charBuffer,
					"Validated dequeued value is correct",
					"Could not validate (dequeued value is NOT correct)");
		}
	}

	success ("Added and removed elements to the queue and validated "
			"appropriately\n");

	// Validate completely deleted queue

	assert (0 == queueSize (&sTheQueue), "Fully deleted queue size is 0",
			"Fully deleted queue size is NOT 0");
	assert (queueIsEmpty (&sTheQueue), "Fully deleted queue is empty\n",
			"Fully deleted queue is NOT empty\n");

	// Add and remove different types into the same queue and validate

	for (j = 0; j < LONG_QUEUE_LENGTH; j++)
	{
		if (0 == j % EVEN)
		{
			queueEnqueue (&sTheQueue, &j, sizeof (int));
		}
		else
		{
			floatBuffer = (float) j;
			queueEnqueue (&sTheQueue, &floatBuffer, sizeof (float));
		}
	}

	for (j = 0; j < LONG_QUEUE_LENGTH; j++)
	{
		if (0 == j % EVEN)
		{
			queueDequeue (&sTheQueue, &intBuffer, sizeof (int));
			if (j != intBuffer)
			{
				assert (j == intBuffer,
						"Validated dequeued value is correct",
						"Could not validate (dequeued value is NOT correct)");
			}
		}
		else
		{
			queueDequeue (&sTheQueue, &floatBuffer, sizeof (float));
			if ((float) j != floatBuffer)
			{
				assert ((float) j == floatBuffer,
						"Validated dequeued value is correct",
						"Could not validate (dequeued value is NOT correct)");
			}
		}
	}

	success ("Added and removed different type elements to the queue and "
			"validated appropriately\n");

	queueTerminate (&sTheQueue);

	puts ("Driver End");

	return EXIT_SUCCESS;
}
