/**************************************************************************
 File name:  listdriver.c
 Author:     Ellysia Li
 Date:			 9.24.2019
 Class:			 CS300
 Assignment: GenericDynamicList
 Purpose:    Test driver for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

#define MAX_BUFFER_CHARS 64

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
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	List sTheList;
	char i, charBuffer, szSuccess[MAX_BUFFER_CHARS], szFailure[MAX_BUFFER_CHARS];

	lstLoadErrorMessages ();

	lstCreate (&sTheList);
	assert (0 == lstSize (&sTheList), "Initial list size is 0",
			"Initial list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Initial list is empty\n",
			"Initial list is NOT empty\n");

	for (i = 'A'; i <= 'E'; i++)
	{
		lstInsertAfter (&sTheList, &i, sizeof(char));

		sprintf (szSuccess, "InsertAfter (current) element is %c", i);
		sprintf (szFailure, "InsertAfter (current) element is NOT %c", i);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		assert (i == charBuffer, szSuccess, szFailure);

		sprintf (szSuccess, "List size is %d", i - 'A' + 1);
		sprintf (szFailure, "List size is NOT %d", i - 'A' + 1);
		assert (i - 'A' + 1 == lstSize (&sTheList), szSuccess, szFailure);

		assert (!lstIsEmpty (&sTheList), "List is NOT empty\n", "List is empty\n");
	}

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('A' == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");

	for (i = 'B'; i <= 'E'; i++))
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

	charBuffer = 'C';
	lstInsertAfter (&sTheList, &charBuffer, sizeof(char));
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('C' == charBuffer, "InsertAfter (current) element is C",
			"InsertAfter (current) element is NOT C");
	charBuffer = '3';
	lstInsertAfter (&sTheList, &charBuffer, sizeof(char));
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('3' == charBuffer, "InsertAfter (current) element is 3",
			"InsertAfter (current) element is NOT 3");
	charBuffer = '0';
	lstInsertAfter (&sTheList, &charBuffer, sizeof(char));
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('0' == charBuffer, "InsertAfter (current) element is 0",
			"InsertAfter (current) element is NOT 0");

	lstFirst (&sTheList);
	charBuffer = 'S';
	lstInsertAfter (&sTheList, &charBuffer, sizeof(char));
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('S' == charBuffer,
			"InsertAfter (current) element is S (attempted to add after C)",
			"InsertAfter (current) element is NOT S (attempted to add after C)");
	lstNext (&sTheList);
	charBuffer = '0';
	lstInsertAfter (&sTheList, &charBuffer, sizeof(char));
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('0' == charBuffer,
			"InsertAfter (current) element is 0 (attempted to add after 3)\n",
			"InsertAfter (current) element is NOT 0 (attempted to add after 3)\n");

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('C' == charBuffer, "lstFirst moved (first) element is C",
			"lstFirst moved (first) element is NOT C");
	lstNext (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('S' == charBuffer, "lstNext element is S",
			"lstNext element is NOT S");
	lstNext (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('3' == charBuffer, "lstNext element is 3",
			"lstNext element is NOT 3");
	lstNext (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('0' == charBuffer, "lstNext element is 0",
			"lstNext element is NOT 0");
	lstNext (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert ('0' == charBuffer, "lstNext element is 0",
			"lstNext element is NOT 0");

	return EXIT_SUCCESS;
}
