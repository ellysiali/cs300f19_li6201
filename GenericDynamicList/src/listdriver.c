/**************************************************************************
 File name:  listdriver.c
 Author:     Ellysia Li
 Date:		 	 10.1.2019
 Class:		 	 CS300
 Assignment: GenericDynamicList
 Purpose:    Test driver for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

#define MAX_BUFFER_CHARS 100
#define CHAR_START 65
#define CHAR_END 90
#define LARGE_LIST_SIZE 10000
#define VERY_LARGE_LIST_SIZE 1000000
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

	puts ("Driver Started\n");

	lstLoadErrorMessages ();

	// Validate the initiated list (after lstCreate)

	lstCreate (&sTheList);
	assert (0 == lstSize (&sTheList), "Initial list size is 0",
			"Initial list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Initial list is empty",
			"Initial list is NOT empty");
	assert (!lstHasCurrent (&sTheList), "Initial list psCurrent is NULL\n",
			"Initial list psCurrent is NOT NULL\n");

	// Add chars using lstInsertAfter and validate appropriately

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		lstInsertAfter (&sTheList, &i, sizeof(char));
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		if (i != charBuffer)
		{
			assert (i == charBuffer, "Added char elements and validated",
					"Could not lstInsertAfter all char elements "
							"(couldn't validate lstPeek)");
		}
		if (i - CHAR_START + 1 != lstSize (&sTheList))
		{
			assert (i - CHAR_START + 1 == lstSize (&sTheList),
					"Added char elements and validated",
					"Could not lstInsertAfter all char elements "
							"(couldn't validate lstSize)");
		}
		if (lstIsEmpty (&sTheList))
		{
			assert (!lstIsEmpty (&sTheList), "Added char elements and validated",
					"Could not lstInsertAfter all char elements "
							"(couldn't validate lstIsEmpty)");
		}
		if (!lstHasCurrent (&sTheList))
		{
			assert (lstHasCurrent (&sTheList), "Added char elements and validated",
					"Could not lstInsertAfter all char elements "
							"(couldn't validate lstHasCurrent)");
		}
		if (lstHasNext (&sTheList))
		{
			assert (!lstHasNext (&sTheList), "Added char elements and validated",
					"Could not lstInsertAfter all char elements "
							"(couldn't validate lstHasNext)");
		}
	}

	// Validate lstFirst and lsLast

	lstFirst (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_START == charBuffer, "lstFirst moved (first) element is A",
			"lstFirst moved (first) element is NOT A");

	lstLast (&sTheList);
	lstPeek (&sTheList, &charBuffer, sizeof(char));
	assert (CHAR_END == charBuffer, "lstLast moved (last) element is E\n",
			"lstLast moved (last) element is NOT E\n");

	// Validate within the middle of the list appropriately

	lstFirst (&sTheList);
	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		sprintf (szSuccess, "lstNext element is %c", i);
		sprintf (szFailure, "lstNext element is NOT %c", i);
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		assert (charBuffer == i, szSuccess, szFailure);
		if (!lstHasCurrent (&sTheList))
		{
			assert (lstHasCurrent (&sTheList), "lsthasNext procedure validated",
					"Could not validate lstHasCurrent in lsthasNext procedure");
		}
		if (CHAR_END != i)
		{
			sprintf (szSuccess, "lstPeekNext element is %c", i + 1);
			sprintf (szFailure, "lstPeekNext element is NOT %c", i + 1);
			lstPeekNext (&sTheList, &charBuffer, sizeof(char));
			assert (charBuffer == i + 1, szSuccess, szFailure);
			if (!lstHasCurrent (&sTheList))
			{
				assert (!lstHasNext (&sTheList), "lsthasNext procedure validated",
						"Could not validate lstHasNext in lsthasNext procedure");
			}
		}
		else if (lstHasNext (&sTheList))
		{
			assert (!lstHasNext (&sTheList), "lsthasNext procedure validated",
					"Could not validate lstHasNext in lsthasNext procedure");
		}
		lstNext (&sTheList);
	}
	puts ("");

	// Validate lstTerminate on a non-empty list

	lstTerminate (&sTheList);
	assert (0 == lstSize (&sTheList), "Terminated list size is 0",
			"Terminated list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Terminated list is empty",
			"Terminated list is NOT empty");
	assert (!lstHasCurrent (&sTheList), "Terminated list psCurrent is NULL\n",
			"Terminated list psCurrent is NOT NULL\n");

	// Validate order of lstInsertAfter when inserting in the middle of the list

	lstCreate (&sTheList);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		if (1 == i % 2)
		{
			lstInsertAfter (&sTheList, &i, sizeof(char));
		}
	}

	lstFirst (&sTheList);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		if (0 == i % 2)
		{
			lstInsertAfter (&sTheList, &i, sizeof(char));
			lstNext (&sTheList);
		}
	}

	lstFirst (&sTheList);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		if (i != charBuffer)
		{
			assert (i == charBuffer,
					"Validated order when adding to middle via lstInsertAfter",
					"Could not validate order when adding to middle via lstInsertAfter");
		}
		lstNext (&sTheList);
	}

	lstTerminate (&sTheList);

	// Add chars using lstInsertBefore and validate appropriately

	lstCreate (&sTheList);

	for (i = CHAR_END; CHAR_START <= i; i--)
	{
		lstInsertBefore (&sTheList, &i, sizeof(char));
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		if (i != charBuffer)
		{
			assert (i == charBuffer, "Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstPeek)");
		}
		if (CHAR_END - i + 1 != lstSize (&sTheList))
		{
			assert (CHAR_END - i + 1 == lstSize (&sTheList),
					"Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstSize)");
		}
		if (lstIsEmpty (&sTheList))
		{
			assert (!lstIsEmpty (&sTheList), "Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstIsEmpty)");
		}
		if (!lstHasCurrent (&sTheList))
		{
			assert (lstHasCurrent (&sTheList), "Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstHasCurrent)");
		}
		if (CHAR_END == i && lstHasNext (&sTheList))
		{
			assert (!lstHasNext (&sTheList), "Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstHasNext)");
		}
		if (CHAR_END != i && !lstHasNext (&sTheList))
		{
			assert (lstHasNext (&sTheList), "Added char elements and validated",
					"Could not lstInsertBefore all char elements "
							"(couldn't validate lstHasNext)");
		}
	}

	lstTerminate (&sTheList);

	// Validate order of lstInsertBefore when inserting in the beginning/middle
	// of the list

	lstCreate (&sTheList);

	for (i = CHAR_END; CHAR_START <= i; i--)
	{
		if (0 == i % 2)
		{
			lstInsertBefore (&sTheList, &i, sizeof(char));
		}
	}

	lstFirst (&sTheList);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		if (1 == i % 2)
		{
			lstInsertBefore (&sTheList, &i, sizeof(char));
			lstNext (&sTheList);
			lstNext (&sTheList);
		}
	}

	lstFirst (&sTheList);

	for (i = CHAR_START; CHAR_END >= i; i++)
	{
		lstPeek (&sTheList, &charBuffer, sizeof(char));
		if (i != charBuffer)
		{
			assert (i == charBuffer,
					"Validated order when adding to middle via lstInsertAfter",
					"Could not validate order when adding to middle via lstInsertAfter");
		}
		lstNext (&sTheList);
	}

	lstTerminate (&sTheList);

	// Create a large list and validate lstDeleteCurrent

	lstCreate (&sTheList);

	for (j = 0; LARGE_LIST_SIZE >= j; j++)
	{
		lstInsertAfter (&sTheList, &j, sizeof(int));
	}

	for (j = 0; LARGE_LIST_SIZE >= j; j++)
	{
		lstDeleteCurrent (&sTheList, &intBuffer, sizeof(int));
		if (LARGE_LIST_SIZE - j != lstSize (&sTheList))
		{
			assert (LARGE_LIST_SIZE - j == lstSize (&sTheList),
					"Deleted list is correct size", "Deleted list is NOT correct size");
		}
	}

	assert (0 == lstSize (&sTheList), "Fully deleted list size is 0",
			"Fully deleted list size is NOT 0");
	assert (lstIsEmpty (&sTheList), "Fully deleted list is empty",
			"Fully deleted list is NOT empty");
	assert (!lstHasCurrent (&sTheList), "Fully deleted list psCurrent is NULL\n",
			"Fully deleted list psCurrent is NOT NULL\n");

	// Validate lstDeleteCurrent when deleting at the beginning/middle of list

	for (j = DELETE_FIRST; DELETE_LAST >= j; j++)
	{
		lstInsertAfter (&sTheList, &j, sizeof(int));
	}

	lstFirst (&sTheList);

	lstDeleteCurrent (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_FIRST == intBuffer, "Deleted first element (0)",
			"Did NOT delete first element (0)");
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_MID == intBuffer, "Current (peeked) element is 1",
			"Current (peeked) element is NOT 1");

	intBuffer = DELETE_FIRST;
	lstInsertBefore (&sTheList, &intBuffer, sizeof(int));

	lstNext (&sTheList);
	lstDeleteCurrent (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_MID == intBuffer, "Deleted middle element (1)",
			"Did NOT delete middle element (1)");
	lstPeek (&sTheList, &intBuffer, sizeof(int));
	assert (DELETE_FIRST == intBuffer, "Current (peeked) element is 0\n",
			"Current (peeked) element is NOT 0\n");

	intBuffer = DELETE_MID;
	lstInsertAfter (&sTheList, &intBuffer, sizeof(int));

	lstTerminate (&sTheList);

	// Validate lstUpdateCurrent in a very large list

	lstCreate (&sTheList);

	for (j = 0; VERY_LARGE_LIST_SIZE >= j; j++)
	{
		lstInsertAfter (&sTheList, &j, sizeof(int));
	}

	lstFirst (&sTheList);

	for (k = 0; VERY_LARGE_LIST_SIZE >= k; k++)
	{
		if (0 == (int) k % 2)
		{
			lstUpdateCurrent (&sTheList, &k, sizeof(float));
		}
		lstNext (&sTheList);
	}

	lstFirst (&sTheList);

	for (j = 0; VERY_LARGE_LIST_SIZE >= j; j++)
	{
		if (0 == j % 2)
		{
			lstPeek (&sTheList, &floatBuffer, sizeof(float));
			if ((float) j != floatBuffer)
			{
				assert ((float) j == floatBuffer, "Updated current",
						"Could not validate lstUpdateCurrent (on float)");
			}
		}
		else
		{
			lstPeek (&sTheList, &intBuffer, sizeof(int));
			if (j != intBuffer)
			{
				assert (j == intBuffer, "Updated current",
						"Could not validate lstUpdateCurrent (on int)");
			}
		}
		lstNext (&sTheList);
	}

	lstTerminate (&sTheList);

	puts ("Driver Terminated");

	return (EXIT_SUCCESS);
}
