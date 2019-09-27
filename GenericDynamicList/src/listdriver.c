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
#define FLOAT_START 1.00
#define FLOAT_END 6.00
#define DELETE_FIRST 0
#define DELETE_MID 1
#define DELETE_LAST 2

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
	List sTheList;
	char i, charBuffer, szSuccess[MAX_BUFFER_CHARS], szFailure[MAX_BUFFER_CHARS];
	int j, intBuffer;
	float k, floatBuffer;

	lstLoadErrorMessages ();

	lstCreate (&sTheList);
	assert (0 == lstSize (&sTheList), "Initial list size is 0",
			"Initial list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Initial list is empty",
			"Initial list is NOT empty");
	assert (!lstHasCurrent(&sTheList), "Initial list psCurrent is NULL\n",
			"Initial list psCurrent is NOT NULL\n");

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

		assert (!lstIsEmpty (&sTheList), "List is NOT empty", "List is empty");
		assert (lstHasCurrent(&sTheList), "List psCurrent is NOT NULL",
				"List psCurrent is NULL");
		assert (!lstHasNext(&sTheList), "List psCurrent has NO successor\n",
				"List psCurrent has a successor\n");
	}

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_START == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");

	lstLast (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_END == charBuffer, "lstLast moved (last) element is E\n",
			"lstLast moved (last) element is NOT E\n");

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_START == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");
	assert (lstHasCurrent(&sTheList), "List psCurrent is NOT NULL",
			"List psCurrent is NULL");
	assert (lstHasNext (&sTheList), "List psCurrent has a successor\n",
			"List psCurrent has NO successor\n");

	for (i = CHAR_START + 1; CHAR_END >= i; i++)
	{
		lstNext (&sTheList);
		sprintf (szSuccess, "lstNext element is %c", i);
		sprintf (szFailure, "lstNext element is NOT %c", i);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		assert (charBuffer == i, szSuccess, szFailure);
		assert (lstHasCurrent(&sTheList), "List psCurrent is NOT NULL",
				"List psCurrent is NULL");
		if (CHAR_END != i)
		{
			assert (lstHasNext (&sTheList), "List psCurrent has a successor\n",
					"List psCurrent has NO successor\n");
		}
		else
		{
			assert (!lstHasNext(&sTheList), "List psCurrent has NO successor\n",
					"List psCurrent has a successor\n");
		}
	}

	lstTerminate (&sTheList);
	assert (0 == lstSize (&sTheList), "Terminated list size is 0",
			"Terminated list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Terminated list is empty",
			"Terminated list is NOT empty");
	assert (!lstHasCurrent(&sTheList), "Terminated list psCurrent is NULL\n",
			"Terminated list psCurrent is NOT NULL\n");

	lstCreate (&sTheList);

	for (j = INT_START; j <= INT_END; j++)
	{
		if (1 == j % 2)
		{
			lstInsertAfter (&sTheList, &j, sizeof(int));
			sprintf (szSuccess, "InsertAfter (current) element is %d", j);
			sprintf (szFailure, "InsertAfter (current) element is NOT %d", j);
			lstPeek (&sTheList, &intBuffer, sizeof(int));
			assert (intBuffer == j, szSuccess, szFailure);
		}
	}

	lstFirst (&sTheList);
	for (j = INT_START; INT_END >= j; j++)
	{
		if (0 == j % 2)
		{
			lstInsertAfter (&sTheList, &j, sizeof(int));
			sprintf (szSuccess, "InsertAfter (current) element is %d "
					"(attempted to add after %d)", j, j - 1);
			sprintf (szFailure, "InsertAfter (current) element is NOT %d "
					"(attempted to add after %d)", j, j - 1);
			lstPeek (&sTheList, &intBuffer, sizeof(int));
			assert (intBuffer == j, szSuccess, szFailure);
			lstNext (&sTheList);
		}
	}

	puts ("");
	lstFirst (&sTheList);
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (INT_START == intBuffer, "lstFirst moved (first) element is 1",
			"lstFirst moved (first) element is NOT 1");

	for (j = INT_START + 1; INT_END >= j; j++)
	{
		lstNext (&sTheList);
		sprintf (szSuccess, "lstNext element is %d", j);
		sprintf (szFailure, "lstNext element is NOT %d", j);
		lstPeek (&sTheList, &intBuffer, sizeof(int));
		assert (j == intBuffer, szSuccess, szFailure);
	}

	lstTerminate (&sTheList);
	lstCreate (&sTheList);

	puts ("");

	j = 0;
	for (k = FLOAT_END; FLOAT_START <= k; k = k - 1)
	{
		if (0 == (int) k % 2)
		{
			j++;

			lstInsertBefore (&sTheList, &k, sizeof(float));

			sprintf (szSuccess, "InsertBefore (current) element is %.2f", k);
			sprintf (szFailure, "InsertBefore (current) element is NOT %.2f", k);
			lstPeek (&sTheList, &floatBuffer, sizeof(float));
			assert (k == floatBuffer, szSuccess, szFailure);

			sprintf (szSuccess, "List size is %d", j);
			sprintf (szFailure, "List size is NOT %d", j);
			assert (j == lstSize (&sTheList), szSuccess, szFailure);

			assert (!lstIsEmpty (&sTheList), "List is NOT empty", "List is empty");
			assert (lstHasCurrent (&sTheList), "List psCurrent is NOT NULL",
					"List psCurrent is NULL");
			if (1 == j)
			{
				assert (!lstHasNext (&sTheList), "List psCurrent has NO successor\n",
						"List psCurrent has a successor\n");
			}
			else
			{
				assert (lstHasNext (&sTheList), "List psCurrent has a successor\n",
						"List psCurrent has NO successor\n");
			}
		}
	}

	lstFirst (&sTheList);

	for (k = FLOAT_START; FLOAT_END >= k; k = k + 1)
	{
		if (1 == (int) k % 2)
		{
			lstInsertBefore (&sTheList, &k, sizeof(float));

			sprintf (szSuccess, "InsertBefore (current) element is %.2f "
					"(attempted to add before %.2f)", k, k + 1);
			sprintf (szFailure, "InsertBefore (current) element is NOT %.2f "
					"(attempted to add before %.2f)", k, k + 1);
			lstPeek (&sTheList, &floatBuffer, sizeof(float));
			assert (k == floatBuffer, szSuccess, szFailure);

			lstNext (&sTheList);
			lstNext (&sTheList);
		}
	}

	puts ("");
	lstFirst (&sTheList);
	lstPeek (&sTheList, &floatBuffer, sizeof(float));
	assert (FLOAT_START == floatBuffer, "lstFirst moved (first) element is 1.00",
			"lstFirst moved (first) element is NOT 1.00");
	for (k = FLOAT_START + 1; FLOAT_END >= k; k = k + 1)
	{
		lstNext (&sTheList);
		sprintf (szSuccess, "lstNext element is %.2f", k);
		sprintf (szFailure, "lstNext element is NOT %.2f", k);
		lstPeek (&sTheList, &floatBuffer, sizeof(float));
		assert (k == floatBuffer, szSuccess, szFailure);
	}

	puts ("");

	for (k = 0; FLOAT_END > k; k = k + 1)
	{
		lstDeleteCurrent (&sTheList, &floatBuffer, sizeof(float));
	}
	assert (0 == lstSize (&sTheList), "Fully deleted list size is 0",
			"Fully deleted list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Fully deleted list is empty",
			"Fully deleted list is NOT empty");
	assert (!lstHasCurrent (&sTheList), "Fully deleted list psCurrent is NULL\n",
			"Fully deleted list psCurrent is NOT NULL\n");

	for (j = DELETE_FIRST; DELETE_LAST >= j; j++)
	{
		lstInsertAfter (&sTheList, &j, sizeof(int));
		sprintf (szSuccess, "InsertAfter (current) element is %d", j);
		sprintf (szFailure, "InsertAfter (current) element is NOT %d", j);
		lstPeek (&sTheList, &intBuffer, sizeof(int));
		assert (j == intBuffer, szSuccess, szFailure);
	}

	puts ("");
	lstFirst (&sTheList);

	lstDeleteCurrent (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_FIRST == intBuffer, "Deleted first element (0)",
			"Did NOT delete first element (0)");
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_MID == intBuffer, "Current (peeked) element is 1",
			"Current (peeked) element is NOT 1");

	intBuffer = DELETE_FIRST;
	lstInsertBefore (&sTheList, &intBuffer, sizeof(int));
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_FIRST == intBuffer, "InsertBefore (current) element is 0",
			"InsertBefore (current) element is NOT 0");

	lstNext (&sTheList);
	lstDeleteCurrent (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_MID == intBuffer, "Deleted middle element (1)",
			"Did NOT delete middle element (1)");
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_FIRST == intBuffer, "Current (peeked) element is 0",
			"Current (peeked) element is NOT 0");

	intBuffer = DELETE_MID;
	lstInsertAfter (&sTheList, &intBuffer, sizeof(int));
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_MID == intBuffer, "InsertAfter (current) element is 1\n",
			"InsertAfter (current) element is NOT 1\n");

	lstFirst (&sTheList);

	for (i = CHAR_START; CHAR_START + DELETE_LAST >= i; i++)
	{
		lstPeek (&sTheList, &intBuffer, sizeof(int));
		sprintf (szSuccess, "Current element is %d", i - CHAR_START);
		sprintf (szFailure, "First (current) element is NOT %d", i - CHAR_START);
		assert (i - CHAR_START == intBuffer, szSuccess, szFailure);

		lstUpdateCurrent (&sTheList, &i, sizeof(char));
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		sprintf (szSuccess, "Updated (current) element is %c", i);
		sprintf (szFailure, "Updated (current) element is NOT %c", i);
		assert (i == charBuffer, szSuccess, szFailure);

		lstNext (&sTheList);
	}

	puts ("");
	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_START == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");

	for (i = CHAR_START + 1; CHAR_START + DELETE_LAST >= i; i++)
	{
		lstNext (&sTheList);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		sprintf (szSuccess, "lstNext element is %c", i);
		sprintf (szFailure, "lstNext element is NOT %c", i);
		assert (i == charBuffer, szSuccess, szFailure);
	}

	lstTerminate (&sTheList);

	return (EXIT_SUCCESS);
}
