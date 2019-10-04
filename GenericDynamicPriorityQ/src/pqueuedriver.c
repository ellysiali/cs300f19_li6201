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
	puts ("Start Driver");

	pqueueCreate (&sTheQueue);

	pqueueTerminate (&sTheQueue);

	puts ("End Driver");
	return EXIT_SUCCESS;
}
