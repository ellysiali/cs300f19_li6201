/**************************************************************************
 File name:  list.c
 Author:     Ellysia Li
 Date:			 9.17.2019
 Class:			 CS300
 Assignment: GenericDynamicList
 Purpose:    Implementation for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszListErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstCreate

 Description: Initializes psHead, psTail, psCurrent to NULL (the list is empty)

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	// results: If the list can be created, then the list exists and is empty;
	//					otherwise, ERROR_NO_LIST_CREATE if psList is NULL
}

/**************************************************************************
 Function: 	 	lstTerminate

 Description: Sets psHead, psTail, psCurrent to NULL

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	// results: If the list can be terminated, then the list no longer exists
	// and is empty; otherwise, ERROR_NO_LIST_TERMINATE
}

/**************************************************************************
 Function: 	 	stkLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function: 	 	lstSize

 Description: Returns the number of elements on the list

 Parameters:	psList - pointer to a list

 Returned:	 	Number of elements in the list
 *************************************************************************/
int lstSize (const ListPtr psList)
{
	// results: Returns the number of elements in the list
	// 					error code priority: ERROR_INVALID_LIST
	return 0;
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Checks if the list is empty

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if list is empty otherwise false
 *************************************************************************/
bool lstIsEmpty (const ListPtr psList)
{
	// results: If list is empty, return true; otherwise, return false
	// 					error code priority: ERROR_INVALID_LIST
	return true;
}

/**************************************************************************
 Function: 	 	lstHasCurrent

 Description: Checks if psCurrent is NULL

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if psCurrent is NULL otherwise false
 *************************************************************************/
bool lstHasCurrent (const ListPtr psList)
{
	// results: Returns true if the current node is not NULL; otherwise, false
	//					is returned
	// 				  error code priority: ERROR_INVALID_LIST
	return true;
}

/**************************************************************************
 Function: 	 	lstHasNext

 Description: Checks if psCurrent has a successor

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if psCurrent has a successor otherwise false
 *************************************************************************/
bool lstHasNext (const ListPtr psList)
{
	 // results: Returns true if the current node has a successor; otherwise,
	 //					 false is returned
	 // 				 error code priority: ERROR_INVALID_LIST
	return true;
}

/**************************************************************************
 Function: 	 	lstPeek

 Description: Looks at the value psCurrent is pointing to in the list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer of the peek value
 *************************************************************************/
void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	// requires:  List is not empty
	// results:   The value of the current element is returned
	// IMPORTANT: Do not change current
	//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//											           ERROR_EMPTY_LIST, ERROR_NO_CURRENT
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstPeekNext

 Description: Looks at the value psCurrent's successor is pointing to in the
 	 	 	 	 	 	  list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer of the peek value
 *************************************************************************/
void *lstPeekNext (const ListPtr psList, void *pBuffer, int size)
{
	// requires:  List contains two or more elements and current is not last
	// results:   The data value of current's successor is returned
	// IMPORTANT: Do not change current
	//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//											           ERROR_EMPTY_LIST, ERROR_NO_CURRENT,
	//																 ERROR_NO_NEXT
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstFirst

 Description: Changes psCurrent to the first element in the list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer with the first element's value
 *************************************************************************/
void lstFirst (ListPtr psList)
{
	// requires:  List is not empty
	// results: 	If the list is not empty, current is changed to the first element
	//          	error code priority: ERROR_INVALID_LIST,
	//										  ERROR_EMPTY_LIST
}

/**************************************************************************
 Function: 	 	lstNext

 Description: Changes psCurrent to the next element in the list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer with the former psCurrent's value
 *************************************************************************/
void lstNext (ListPtr psList)
{
	// requires:  List is not empty
	// results:   If the list is not empty, current is changed to the
	//						successor of the current element
	//            error code priority: ERROR_INVALID_LIST,
	//										 ERROR_EMPTY_LIST, ERROR_NO_CURRENT
}

/**************************************************************************
 Function: 	 	lstLast

 Description: Changes psCurrent to the last element in the list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void lstLast (ListPtr psList)
{
	// requires:  List is not empty
	// results:   If the list is not empty, current is changed to last
	//						if it exists
	//            error code priority: ERROR_INVALID_LIST,
	//										 ERROR_EMPTY_LIST
}

/**************************************************************************
 Function: 	 	lstInsertAfter

 Description: Insert the new element as the successor of the current element
 	 	 	 	 	 	  (and make the inserted element the current element)

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	None
 *************************************************************************/
void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	// requires: List is not full
	// results:  If the list is not empty, insert the new element as the
	//           successor of the current element and make the inserted element
	//           the current element; otherwise, insert element and make it
	//					 current.
	//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//																ERROR_NO_CURRENT
}

/**************************************************************************
 Function: 	 	lstDeleteCurrent

 Description: Deletes the current element and adjusts successor and predecessor

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size)
{
	// requires: List is not empty
	// results: The current element is deleted and its successor and
	//				  predecessor become each others successor and predecessor. If
	//					the deleted element had a predecessor, then make it the new
	// 					current element; otherwise, make the first element current if
	// 					it exists. The value of the deleted element is returned.
	//          error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//					                     ERROR_EMPTY_LIST, ERROR_NO_CURRENT
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstInsertBefore

 Description: Insert the new element as the predecessor of the current element
 	 	 	 	 	 	  (and make the inserted element the current element)

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void lstInsertBefore (ListPtr psList, const void *pBuffer,
														 int size)
{
	// requires: List is not full
	// results:  If the list is not empty, insert the new element as the
	//           predecessor of the current element and make the inserted
	//           element the current element; otherwise, insert element
	//           and make it current.
	//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//																ERROR_NO_CURRENT
}

/**************************************************************************
 Function: 	 	lstUpdateCurrent

 Description: Update the current element's value to the value of pBuffer

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	  pBuffer - void pointer used to store the value
 	 	 	 	 	 	  size    - size of value

 Returned:	 	None
 *************************************************************************/
void lstUpdateCurrent (ListPtr psList, const void *pBuffer,
														  int size)
{
	// requires: List is not empty
	// results:  The value of pBuffer is copied into the current element
	//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
	//					                       ERROR_EMPTY_LIST, ERROR_NO_CURRENT
	// IMPORTANT: user could update with smaller, larger, or the same size data
	//					  so free data, then reallocate based on size before updating
}

/**************************************************************************
 Function: 	 	lstReverse

 Description: Reverse the order of the list

 Parameters:	psList  - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstReverse(ListPtr psList)
{

}
