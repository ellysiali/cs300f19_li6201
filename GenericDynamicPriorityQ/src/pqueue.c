/**************************************************************************
 File name:  pqueue.c
 Author:     Ellysia Li
 Date:		 	 Oct 3, 2019
 Class:		 	 CS300
 Assignment: Priority Queue Implementation
 Purpose:    Implementation for a priority queue data structure
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/pqueue.h"
#include "../../GenericDynamicList/include/list.h"

char gszPQErrors[NUMBER_OF_PQ_ERRORS][MAX_ERROR_PQ_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszPQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	pqueueCreate

 Description: Initializes the list in the priority queue

 Parameters:	psQueue - pointer to the priority queue

 Returned:	 	None
 *************************************************************************/
void pqueueCreate (PriorityQueuePtr psQueue
													/*, 	cmpFunction cmpFunct */)
{
	if (NULL == psQueue)
	{
		processError ("pqueueCreate", ERROR_NO_PQ_CREATE);
	}
	lstCreate (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueTerminate

 Description: Terminates the list as well as the data in the queue elements

 Parameters:	psQueue - pointer to the priority queue

 Returned:	 	None
 *************************************************************************/
void pqueueTerminate (PriorityQueuePtr psQueue)
{
	PriorityQueueElementPtr psQElementBuffer;
	if (NULL == psQueue)
	{
		processError ("pqueueCreate", ERROR_NO_PQ_TERMINATE);
	}
	while (0 != lstSize (&psQueue->sTheList))
	{
		lstFirst (&psQueue->sTheList);
		lstDeleteCurrent (&psQueue->sTheList, psQElementBuffer,
				sizeof (PriorityQueueElement));
		free (psQElementBuffer->pData);
	}
}
// results: If PQ can be terminated, then PQ no longer exists and is empty
//				   otherwise, ERROR_NO_PQ_TERMINATE

/**************************************************************************
 Function: 	 	pqueueLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void pqueueLoadErrorMessages ()
{
	LOAD_PQ_ERRORS
}

/**************************************************************************
 Function: 	 	pqueueSize

 Description: Returns the size of the priority queue

 Parameters:	psQueue - pointer to the priority queue

 Returned:	 	Size of the queue
 *************************************************************************/
int pqueueSize (const PriorityQueuePtr psQueue)
{
	return 0;
}
// results: Returns the number of elements in the PQ
// 					error code priority: ERROR_INVALID_PQ if PQ is NULL

/**************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: Checks if the priority queue is empty

 Parameters:	psQueue - pointer to the priority queue

 Returned:	 	True if queue is empty otherwise false
 *************************************************************************/
bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	return true;
}
// results: If PQ is empty, return true{} otherwise, return false
// 					error code priority: ERROR_INVALID_PQ

/**************************************************************************
 Function: 	 	pqueueEnqueue

 Description: Adds a value to the priority queue

 Parameters:	psQueue  - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer  - pointer to value
 	 	 	 	 	 	 	size     - size of value
 	 	 	 	 	 	 	priority - priority of value

 Returned:	 	None
 *************************************************************************/
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
}
// requires: psQueue is not full
// results: Insert the element into the priority queue based on the
//          priority of the element.
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_FULL_PQ

/**************************************************************************
 Function: 	 	pqueueDequeue

 Description: Removes the first value from the priority queue

 Parameters:	psQueue   - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer   - pointer to store the removed value
 	 	 	 	 	 	 	size      - size of the removed value
 	 	 	 	 	 	 	pPriority - pointer to store the priority of the removed value

 Returned:	 	None
 *************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int *pPriority)
{
	return pBuffer;
}
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_EMPTY_PQ

/**************************************************************************
 Function: 	 	pqueuePeek

 Description: Peek at the first value of the priority queue

 Parameters:	psQueue  - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer  - pointer to store the peeked value
 	 	 	 	 	 	 	size     - size of the peeked value
 	 	 	 	 	 	 	priority - pointer to store the priority of the peeked value

 Returned:	 	None
 *************************************************************************/
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority)
{
	return pBuffer;
}
// requires: psQueue is not empty
// results: The priority and value of the first element is returned through
//					the argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//																 ERROR_EMPTY_PQ

/**************************************************************************
 Function: 	 	pqueueChangePriority

 Description: Update all priorities by the value given

 Parameters:	psQueue - pointer to the priority queue
 	 	 	 	 	 	 	change  - value to update by

 Returned:	 	None
 *************************************************************************/
void pqueueChangePriority (PriorityQueuePtr psQueue,
																	int change)
{
}
// results: The priority of all elements is increased by the amount in
//					change error code priority: ERROR_INVALID_PQ
