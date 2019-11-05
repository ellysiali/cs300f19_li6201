/**************************************************************************
 File name:  tree.c
 Author:     Ellysia Li
 Date:		 	 Nov 10, 2019
 Class:		   CS300
 Assignment: Trees
 Purpose:    Implementation of a Binary Search Tree
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/tree.h"

char gszTreeErrors[TR_NUMBER_OF_ERRORS][TR_MAX_ERROR_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the struct error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszTreeErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	trLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
extern void trLoadErrorMessages ()
{
	LOAD_ERRORS
}

/**************************************************************************
 Function: 	 	trCreate

 Description: Initializes the tree handle (to NULL)

 Parameters:	hsTree - handle to the tree

 Returned:	 	None
 *************************************************************************/
extern void trCreate (TreeNodePtr *hsTree)
{
	if (NULL == hsTree)
	{
		processError ("trCreate", TR_NO_CREATE_ERROR);
	}
	(*hsTree) = NULL;
}

/**************************************************************************
 Function: 	 	trTerminate

 Description: Terminates the tree (freeing all nodes)

 Parameters:	hsTree - handle to the tree

 Returned:	 	None
 *************************************************************************/
extern void trTerminate (TreeNodePtr *hsTree)
{
	if (NULL == hsTree)
	{
		processError ("trTerminate", TR_NO_TERMINATE_ERROR);
	}

	// Walk the tree post order and free

	if (NULL != *hsTree)
	{
		if (NULL != (*hsTree)->psLeft)
		{
			trTerminate (&(*hsTree)->psLeft);
		}
		if (NULL != (*hsTree)->psRight)
		{
			trTerminate (&(*hsTree)->psRight);
		}
		free (*hsTree);
		*hsTree = NULL;
	}
}

/**************************************************************************
 Function: 	 	trIsEmpty

 Description: Returns whether the tree is empty

 Parameters:	psTree - pointer to the root of the tree

 Returned:	 	True if the tree is empty; false otherwise
 *************************************************************************/
extern bool trIsEmpty (const TreeNodePtr psTree)
{
	return NULL == psTree;
}

/**************************************************************************
 Function: 	 	trInsert

 Description: Inserts a node into the tree

 Parameters:	hsTree - handle to the tree
 	 	 	 	 	 	 	key		 - the key for the node
 	 	 	 	 	 	 	value  - the value of the node

 Returned:	 	True if the key is not in the tree; false otherwise
 *************************************************************************/
extern bool trInsert (TreeNodePtr *hsTree, const char* key, int value)
{
	bool bValid;
	int compare;

	if (NULL == hsTree)
	{
		processError ("trInsert", TR_NO_MEMORY_ERROR);
	}

	// Check first if tree is empty

	if (trIsEmpty (*hsTree))
	{
		(*hsTree) = (TreeNodePtr) malloc (sizeof (TreeNode));
		(*hsTree)->count = value;
		strncpy ((*hsTree)->szWord, key, WORD_MAX);
		(*hsTree)->psLeft = NULL;
		(*hsTree)->psRight = NULL;
		return true;
	}

	compare = strncmp ((*hsTree)->szWord, key, WORD_MAX);

	// Check if key is valid

	if (0 == compare)
	{
		bValid = false;
	}

	// Step to left child or insert node (when child is NULL)

	if (0 < compare)
	{
		if (NULL != (*hsTree)->psLeft)
		{
			bValid = trInsert (&(*hsTree)->psLeft, key, value);
		}
		else
		{
			bValid = true;
			(*hsTree)->psLeft = (TreeNodePtr) malloc (sizeof (TreeNode));
			(*hsTree)->psLeft->count = value;
			strncpy ((*hsTree)->psLeft->szWord, key, WORD_MAX);
			(*hsTree)->psLeft->psLeft = NULL;
			(*hsTree)->psLeft->psRight = NULL;
		}
	}

	// Check if step to right child or insert node (when child is NULL)

	else if (0 > compare)
	{
		if (NULL != (*hsTree)->psRight)
		{
			bValid = trInsert (&(*hsTree)->psRight, key, value);
		}
		else
		{
			bValid = true;
			(*hsTree)->psRight = (TreeNodePtr) malloc (sizeof (TreeNode));
			(*hsTree)->psRight->count = value;
			strncpy ((*hsTree)->psRight->szWord, key, WORD_MAX);
			(*hsTree)->psRight->psLeft = NULL;
			(*hsTree)->psRight->psRight = NULL;
		}
	}
	return bValid;
}

/**************************************************************************
 Function: 	 	trUpdate

 Description: Updates a node on the tree

 Parameters:	psTree - pointer to the root of the tree
 	 	 	 	 	 	 	key		 - key to search for/update
 	 	 	 	 	 	 	value  - the value to update to

 Returned:	 	True if the key is in the tree and has been updated;
 	 	 	 	 	 	 	false otherwise
 *************************************************************************/
extern bool trUpdate (TreeNodePtr psTree, const char* key, int value)
{
	bool bFound = false;
	int compare;

	if (NULL == psTree)
	{
		return false;
	}

	compare = strncmp (psTree->szWord, key, WORD_MAX);

	if (0 == compare)
	{
		bFound = true;
		psTree->count = value;
	}
	else if (0 < compare && NULL != psTree->psLeft)
	{
		bFound = trUpdate (psTree->psLeft, key, value);
	}
	else if (NULL != psTree->psRight)
	{
		bFound = trUpdate (psTree->psRight, key, value);
	}

	return bFound;
}
/**************************************************************************
 Function: 	 	trFind

 Description: Finds a node on the tree

 Parameters:	psTree - pointer to the root of the tree
 	 	 	 	 	 	 	key		 - key to search for
 	 	 	 	 	 	 	pvalue - the pointer used to pass back the node value

 Returned:	 	True if the key is in the tree; false otherwise
 *************************************************************************/
extern bool trFind (const TreeNodePtr psTree, const char* key, int *pValue)
{
	bool bFound = false;
	int compare;

	if (NULL == pValue)
	{
		processError ("trFind", TR_NO_BUFFER_ERROR);
	}

	if (NULL == psTree)
	{
		return false;
	}

	compare = strncmp (psTree->szWord, key, WORD_MAX);

	if (0 == compare)
	{
		bFound = true;
		memcpy (pValue, &psTree->count, sizeof (int));
	}
	else if (0 < compare && NULL != psTree->psLeft)
	{
		bFound = trFind (psTree->psLeft, key, pValue);
	}
	else if (NULL != psTree->psRight)
	{
		bFound = trFind (psTree->psRight, key, pValue);
	}

	return bFound;
}

/**************************************************************************
 Function: 	 	trPrintInOrder

 Description: Print the keys and values for each node in key order (ascending)

 Parameters:	psTree - pointer to the root of the tree

 Returned:	 	None
 *************************************************************************/
extern void trPrintInOrder(const TreeNodePtr psTree)
{
	// Walk the tree in order and print after walking left

	if (NULL != psTree->psLeft)
	{
		trPrintInOrder (psTree->psLeft);
	}

	printf ("%s %d\n", psTree->szWord, psTree->count);

	if (NULL != psTree->psRight)
	{
		trPrintInOrder (psTree->psRight);
	}
}
