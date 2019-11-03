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
	*hsTree = (TreeNodePtr) malloc (sizeof (TreeNode));
	(*hsTree)->count = 0;
	(*hsTree)->psLeft = NULL;
	(*hsTree)->psRight = NULL;
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
		processError ("trCreate", TR_NO_TERMINATE_ERROR);
	}

	// Walk the tree post order

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

/**************************************************************************
 Function: 	 	trIsEmpty

 Description: Returns whether the tree is empty

 Parameters:	psTree - pointer to the root of the tree

 Returned:	 	True if the tree is empty; false otherwise
 *************************************************************************/
extern bool trIsEmpty (const TreeNodePtr psTree)
{
	if (NULL == psTree)
	{
		processError ("trIsEmpty", TR_NO_MEMORY_ERROR);
	}
	return 0 == psTree->count;
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
		strncpy ((*hsTree)->szWord, key, WORD_MAX);
		(*hsTree)->count += value;
		return true;
	}

	compare = strncmp ((*hsTree)->szWord, key, WORD_MAX);

	// Check if key is valid

	if (0 == compare)
	{
		bValid = false;
	}

	// Check if step to left child or insert node (when child is NULL)

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
	return true;
}
// results: if the tree is valid, and the key does exist in the
//					tree, update the node with the new value passed in and return
//					true.  If the key does not exist in the tree, return false
//					and do not alter the tree.
//					error code priority: TR_NO_MEMORY_ERROR

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
	return true;
}
// results: if the tree is valid, and the key does exist in the
//					tree, return the value through pValue and return true.
//					The user must supply valid memory for pValue.
//					This function does not call malloc.
//				 	If the key does not exist in the tree, return false;
//					error code priority: TR_NO_MEMORY_ERROR, TR_NO_BUFFER_ERROR

/**************************************************************************
 Function: 	 	trPrintInOrder

 Description: Print the keys and values for each node in key order (ascending)

 Parameters:	psTree - pointer to the root of the tree

 Returned:	 	None
 *************************************************************************/
extern void trPrintInOrder(const TreeNodePtr psTree)
{

}
// results: if the tree is valid, print the key and value for each node
//					in key order (ascending).
//					error code priority: TR_NO_MEMORY_ERROR