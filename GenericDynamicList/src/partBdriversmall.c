/**************************************************************************
 File name:  partBdriversmall.c
 Author:     Computer Science, Pacific University
 Date:
 Class:
 Assignment:
 Purpose:
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "../include/list.h"

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
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
/**************************************************************************
 Function: 	 	printList

 Description: Prints a list of integers for debugging purposes.

 Parameters:	sTheList - the list of integers to be printed

 Returned:	 	none
 *************************************************************************/
//static void printIntList (List sTheList)
//{
//	int i, theIntData;
//
//	if (!lstIsEmpty (&sTheList))
//	{
//		printf ("         ");
//		lstFirst (&sTheList);
//		for (i = 0; i < lstSize (&sTheList); ++i)
//		{
//			lstPeek(&sTheList, &theIntData, sizeof(int));
//			printf ("%d ", theIntData);
//
//			lstNext (&sTheList);
//		}
//		printf ("\n");
//	}
//}
/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none
 Returned:	 	none
 *************************************************************************/

int main ()
{
	List sTheList;
	int i, intValue;
	int numValues;
	int count;
	char *szData = "CS300";
	char charValue;
	long long longLongValue = LLONG_MAX;

	lstLoadErrorMessages();
	puts ("Driver Start");

	// run everything twice so you call
	// create after terminate!
	for (count = 0; count < 2 ; ++count)
	{
		lstCreate (&sTheList);
		success ("List Created");

		assert( 0 == lstSize (&sTheList), "The list size is 0",
				"The list size is not 0");


		assert( lstIsEmpty (&sTheList), "The list is empty",
				"The list is not empty");

		numValues = 10;
		for (i = 0; i < numValues; ++i)
		{
			lstInsertAfter (&sTheList, &i, sizeof (int));

			if( i+1 != lstSize (&sTheList) )
			{
				assert( i+1 == lstSize (&sTheList), "The list size correctly sized",
					"The list size is wrong");
			}
		}

		lstFirst (&sTheList);
		i = 0;
		while(lstHasCurrent(&sTheList))
		{
			lstPeek(&sTheList, &intValue, sizeof(int));
			if (i != intValue)
			{
				assert( i == intValue, "Peek returns the correct value (int)",
						"Peek return the incorrect value (int)");
			}
			intValue += 1;
			lstUpdateCurrent(&sTheList, &intValue, sizeof(int));

			intValue = 0;

			lstPeek(&sTheList, &intValue, sizeof(int));
			if (i+1 != intValue)
			{
				assert( i+1 == intValue, "Peek returns the correct value (int)",
						"Peek return the incorrect value (int)");
			}

			++i;
			lstNext (&sTheList);
		}

		assert( ! lstIsEmpty (&sTheList), "The list is NOT empty",
				"The list is empty");

		assert( numValues == lstSize (&sTheList), "The list size is 10 ",
				"The list size is not 10");

		// For debugging purposes only
		//printIntList (sTheList);

		lstFirst(&sTheList);

		assert(lstHasNext(&sTheList), "The current has a next!", "The current does not have a next");

		// should be 2
		lstPeekNext(&sTheList, &intValue, sizeof(int));
		assert(2 == intValue, "PeekNext is correct", "PeekNext is wrong");

		// delete the first element!
		lstDeleteCurrent(&sTheList, &intValue, sizeof(int));

		// check new first element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(2 == intValue, "DeleteCurrent & Peek is correct", "DeleteCurrent & Peek is wrong");

		intValue = 99;
		lstInsertBefore(&sTheList, &intValue, sizeof(int));

		// check new first element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(99 == intValue, "InsertBefore & Peek is correct", "InsertBefore & Peek is wrong");

		lstLast(&sTheList);

		// check last element
		lstPeek(&sTheList, &intValue, sizeof(int));
		assert(numValues == intValue, "Last & Peek is correct", "Last & Peek is wrong");

		lstTerminate (&sTheList);
		success ("List Terminated");

	}

	// use char data.
	lstCreate (&sTheList);
	success ("List Created");

	numValues = strlen(szData);
	for (i = 0; i < numValues; ++i)
	{
		lstInsertBefore (&sTheList, &(szData[i]), sizeof (char));
	}

	lstFirst (&sTheList);

	for (i = numValues - 1; i >= 0; --i)
	{
		lstPeek(&sTheList, &charValue, sizeof(char));
		if (szData[i] != charValue)
		{
			assert( szData[i] == charValue, "Peek returns the correct value (char)",
					"Peek return the incorrect value (char)");
		}
		lstNext (&sTheList);
	}

	lstFirst(&sTheList);

	lstUpdateCurrent(&sTheList, &longLongValue, sizeof(long long) );

	longLongValue = 0;

	lstPeek(&sTheList, &longLongValue, sizeof(long long) );

	assert( LLONG_MAX == longLongValue,"Update Current With different size", "Update Current with different size");

	lstNext(&sTheList);
	charValue = '\0';

	lstPeek(&sTheList, &charValue, sizeof(char));
	assert( szData[numValues - 2] == charValue, "Peek after update with size change returns the correct value (char)",
				"Peek after update with size change returns the correct value (char)");


	lstTerminate(&sTheList);
	lstCreate(&sTheList);

	assert( 0 == lstSize (&sTheList), "The list size is 0",
			"The list size is not 0");


	assert( lstIsEmpty (&sTheList), "The list is empty",
			"The list is not empty");
	lstTerminate(&sTheList);

	puts ("Driver End");
	return EXIT_SUCCESS;
}
