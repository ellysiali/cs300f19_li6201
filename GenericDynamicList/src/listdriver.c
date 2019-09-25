/**************************************************************************
 File name:  listdriver.c
 Author:     Ellysia Li
 Date:		 	 9.24.2019
 Class:		 	 CS300
 Assignment: GenericDynamicList
 Purpose:    Test driver for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

#define MAX_BUFFER_CHARS 100
#define CHAR_START 65
#define CHAR_END 69
#define INT_START 1
#define INT_END 10

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
	List sTheList;
	char i, charBuffer, szSuccess[MAX_BUFFER_CHARS], szFailure[MAX_BUFFER_CHARS];
	int j, intBuffer;

	lstLoadErrorMessages ();

	lstCreate (&sTheList);
	assert (0 == lstSize (&sTheList), "Initial list size is 0",
			"Initial list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Initial list is empty\n",
			"Initial list is NOT empty\n");

	for (i = CHAR_START; i <= CHAR_END; i++)
	{
		lstInsertAfter (&sTheList, &i, sizeof(char));

		sprintf (szSuccess, "InsertAfter (current) element is %c", i);
		sprintf (szFailure, "InsertAfter (current) element is NOT %c", i);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		assert (i == charBuffer, szSuccess, szFailure);

		sprintf (szSuccess, "List size is %d", i - CHAR_START + 1);
		sprintf (szFailure, "List size is NOT %d", i - CHAR_START + 1);
		assert (i - CHAR_START + 1 == lstSize (&sTheList), szSuccess, szFailure);

		assert (!lstIsEmpty (&sTheList), "List is NOT empty\n", "List is empty\n");
	}

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_START == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");

	for (i = CHAR_START + 1; i <= CHAR_END; i++)
	{
		lstNext (&sTheList);
		sprintf (szSuccess, "lstNext element is %c", i);
		sprintf (szFailure, "lstNext element is NOT %c", i);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		assert (i == charBuffer, szSuccess, szFailure);
	}

	lstTerminate (&sTheList);
	puts ("");
	assert (0 == lstSize (&sTheList), "Terminated list size is 0\n",
			"Terminated list size is NOT 0\n");

	lstCreate (&sTheList);

	for (j = INT_START; j <= INT_END; j++)
	{
		if (1 == j % 2)
		{
			lstInsertAfter (&sTheList, &j, sizeof(int));
			sprintf (szSuccess, "InsertAfter (current) element is %d", j);
			sprintf (szFailure, "InsertAfter (current) element is NOT %d", j);
			lstPeek (&sTheList, &intBuffer, sizeof(int));
			assert (j == intBuffer, szSuccess, szFailure);
		}
	}

	lstFirst (&sTheList);
	for (j = INT_START; j <= INT_END; j++)
	{
		if (0 == j % 2)
		{
			lstInsertAfter (&sTheList, &j, sizeof(int));
			sprintf (szSuccess, "InsertAfter (current) element is %d "
					"(attempted to add after %d)", j, j - 1);
			sprintf (szFailure, "InsertAfter (current) element is NOT %d "
					"(attempted to add after %d)", j, j - 1);
			lstPeek (&sTheList, &intBuffer, sizeof(int));
			assert (j == intBuffer, szSuccess, szFailure);
			lstNext (&sTheList);
		}
	}

	puts ("");
	lstFirst (&sTheList);
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (INT_START == intBuffer, "lstFirst moved (first) element is 1",
			"lstFirst moved (first) element is NOT 1");

	for (j = INT_START + 1; j <= INT_END; j++)
	{
		lstNext (&sTheList);
		sprintf (szSuccess, "lstNext element is %d", j);
		sprintf (szFailure, "lstNext element is NOT %d", j);
		lstPeek (&sTheList, &intBuffer, sizeof(int));
		assert (j == intBuffer, szSuccess, szFailure);
	}

	lstTerminate (&sTheList);

	return (EXIT_SUCCESS);
}
