/****************************************************************************
 File name:  	pqdriver1.c
 Author:     	chadd williams
 Date:       	Oct 17, 2019
 Class:			 	CS 300
 Assignment:	Priority Queue
 Purpose:			Basic PQ functionality
 ****************************************************************************/

#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
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

/****************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none
 Returned:	 	none
 ****************************************************************************/

int main ()
{
	PriorityQueue sThePQ;
	int dataValue, priorityValue;
	int i;
	const int MAX_ITEMS = 4;
	const int PRIORITY_TWO = 2;

	// MAX_VALUES is the size of the following two arrays
	const int MAX_VALUES = 9;
	// enter these priorities in this order
	int priorityArray [] =  { 1, 10, 5, 0, 11, 4, 6, 5, 5};

	// Use these dataValues matched with the priorities above
	// the data values must come out of the pq in ascending order
	int dataValueArray [] = { 1, 7, 3, 0, 8, 2, 6, 4, 5};

	// prevDataValue must be initialized to a value
	// smaller than each value in dataValueArray
	int prevDataValue = -1;

	const char CHAR_START = 'A';
	char charData;

	puts ("Program Start\n");

	pqueueLoadErrorMessages();

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	assert (pqueueSize (&sThePQ) == 0, "pqueueSize is 0",
																		 "pqueueSize is not 0");

	assert (pqueueIsEmpty (&sThePQ), "pqueueIsEmpty", "!pqueueIsEmpty");


	// priority 0-3
	for( i = 0; i < MAX_ITEMS; ++i)
	{
		pqueueEnqueue (&sThePQ, &i, sizeof (int), i);
	}

	assert (MAX_ITEMS == pqueueSize (&sThePQ), "pqueueSize is correct",
																		 "pqueueSize is not correct");


	// priority 0-3
	for( i = 0; i < MAX_ITEMS; ++i)
	{
		pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);

		if( dataValue != i || priorityValue != i)
		{
			assert(dataValue == i && priorityValue == i, "",
					"Priority 0-3 error");
		}
	}

	assert (pqueueSize (&sThePQ) == 0, "pqueueSize is 0",
																		 "pqueueSize is not 0");

	pqueueTerminate(&sThePQ);

	pqueueCreate (&sThePQ);
	// priority 3-0
	for( i = MAX_ITEMS-1 ; i >= 0; --i)
	{
		charData = CHAR_START + i;
		pqueueEnqueue (&sThePQ, &charData, sizeof (char), i);
	}

	// priority 0-3
	for( i = 0; i < MAX_ITEMS; ++i)
	{
		pqueueDequeue (&sThePQ, &charData, sizeof (char), &priorityValue);

		if( charData != CHAR_START + i || priorityValue != i)
		{
			assert(charData == CHAR_START + i && priorityValue == i, "",
					"Priority 3-0 error");
		}
	}

	// priority 2,2,2,2 (with values 1,2,3,4)
	for( i = 0; i < MAX_ITEMS; ++i)
	{
		pqueueEnqueue (&sThePQ, &i, sizeof (int), PRIORITY_TWO);
	}
	// priority 0-3
	for( i = 0; i < MAX_ITEMS; ++i)
	{
		pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);
		if( dataValue != i || priorityValue != PRIORITY_TWO)
		{
			assert(dataValue == i && priorityValue == PRIORITY_TWO, "",
					"Priority 2,2,2,2 error");
		}
	}

	for( i = 0; i < MAX_VALUES; ++i)
	{

		pqueueEnqueue (&sThePQ, &(dataValueArray[i]),
				sizeof (int), (priorityArray[i]));
	}


	for( i = 0; i < MAX_VALUES; ++i)
	{

		pqueueDequeue (&sThePQ, &dataValue,	sizeof (int), &priorityValue);

		if(!( dataValue > prevDataValue))
		{
			assert(dataValue > prevDataValue, "", "Data values incorrect");
		}
		prevDataValue = dataValue;
	}

	pqueueEnqueue (&sThePQ, &(dataValueArray[0]),
			sizeof (int), (priorityArray[0]));

	assert (!pqueueIsEmpty (&sThePQ), "!pqueueIsEmpty", "pqueueIsEmpty");

	pqueueTerminate(&sThePQ);
	success ("PQ Terminate");


	puts ("\nProgram End");

	return EXIT_SUCCESS;
}
