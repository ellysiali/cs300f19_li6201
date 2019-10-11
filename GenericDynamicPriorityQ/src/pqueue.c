/**************************************************************************
 File name:  pqueue.c
 Author:     Ellysia Li
 Date:		 	 Oct 15, 2019
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
	PriorityQueueElement sQElementBuffer;
	if (NULL == psQueue)
	{
		processError ("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}
	while (!lstIsEmpty (&psQueue->sTheList))
	{
		lstFirst (&psQueue->sTheList);
		lstDeleteCurrent (&psQueue->sTheList, &sQElementBuffer,
				sizeof (PriorityQueueElement));
		free (sQElementBuffer.pData);
	}
}

/**************************************************************************
 Function: 	 	pqueueLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void pqueueLoadErrorMessages ()
{
	lstLoadErrorMessages ();
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
	if (NULL == psQueue)
	{
		processError ("pqueueSize", ERROR_INVALID_PQ);
	}
	return lstSize (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: Checks if the priority queue is empty

 Parameters:	psQueue - pointer to the priority queue

 Returned:	 	True if queue is empty otherwise false
 *************************************************************************/
bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("pqueueIsEmpty", ERROR_INVALID_PQ);
	}
	return lstIsEmpty (&psQueue->sTheList);
}

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
	PriorityQueueElement sQElementNew, sQElementPeeker;
	if (NULL == psQueue)
	{
		processError ("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}
	sQElementNew.pData = malloc (size);
	memcpy (sQElementNew.pData, pBuffer, size);
	sQElementNew.priority = priority;

	if (pqueueIsEmpty (psQueue))
	{
		lstInsertBefore (&psQueue->sTheList, &sQElementNew,
				sizeof (PriorityQueueElement));
	}
	else
	{
		lstLast (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sQElementPeeker,
				sizeof (PriorityQueueElement));
		if (sQElementNew.priority >= sQElementPeeker.priority)
		{
			lstInsertAfter (&psQueue->sTheList, &sQElementNew,
					sizeof (PriorityQueueElement));
		}
		else
		{
			lstFirst (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &sQElementPeeker,
					sizeof (PriorityQueueElement));
			while (sQElementNew.priority >= sQElementPeeker.priority)
			{
				lstNext (&psQueue->sTheList);
				lstPeek (&psQueue->sTheList, &sQElementPeeker,
						sizeof (PriorityQueueElement));
			}
			lstInsertBefore (&psQueue->sTheList, &sQElementNew,
					sizeof (PriorityQueueElement));
		}
	}
}
/**************************************************************************
 Function: 	 	pqueueDequeue

 Description: Removes the first value from the priority queue

 Parameters:	psQueue   - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer   - pointer to store the removed value
 	 	 	 	 	 	 	size      - size of the removed value
 	 	 	 	 	 	 	pPriority - pointer to store the priority of the removed value

 Returned:	 	Pointer to the buffer of the removed value
 *************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int *pPriority)
{
	PriorityQueueElement sQElementBuffer;
	if (NULL == psQueue)
	{
		processError ("pqueueDequeue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}
	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueueDequeue", ERROR_EMPTY_PQ);
	}
	lstFirst (&psQueue->sTheList);
	lstDeleteCurrent (&psQueue->sTheList, &sQElementBuffer,
			sizeof (PriorityQueueElement));
	memcpy (pBuffer, sQElementBuffer.pData, size);
	free (sQElementBuffer.pData);
	*pPriority = sQElementBuffer.priority;
	return pBuffer;
}

/**************************************************************************
 Function: 	 	pqueuePeek

 Description: Peek at the first value's data and priority of the priority queue

 Parameters:	psQueue  - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer  - pointer to store the peeked value
 	 	 	 	 	 	 	size     - size of the peeked value
 	 	 	 	 	 	 	priority - pointer to store the priority of the peeked value

 Returned:	 	Pointer to the buffer of the peeked value
 *************************************************************************/
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority)
{
	PriorityQueueElement sQElementBuffer;
	if (NULL == psQueue)
	{
		processError ("pqueuePeek", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueuePeek", ERROR_NULL_PQ_PTR);
	}
	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueuePeek", ERROR_EMPTY_PQ);
	}
	lstFirst (&psQueue->sTheList);
	lstPeek (&psQueue->sTheList, &sQElementBuffer, sizeof (PriorityQueueElement));
	memcpy (pBuffer, sQElementBuffer.pData, size);
	*priority = sQElementBuffer.priority;
	return pBuffer;
}

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
	PriorityQueueElement sQElementBuffer;
	if (NULL == psQueue)
	{
		processError ("pqueueChangePriority", ERROR_INVALID_PQ);
	}
	if (!pqueueIsEmpty (psQueue))
	{
		lstFirst (&psQueue->sTheList);
		while (lstHasCurrent (&psQueue->sTheList))
		{
			lstPeek (&psQueue->sTheList, &sQElementBuffer,
					sizeof (PriorityQueueElement));
			sQElementBuffer.priority = sQElementBuffer.priority + change;
			lstUpdateCurrent (&psQueue->sTheList, &sQElementBuffer,
					sizeof (PriorityQueueElement));
			lstNext (&psQueue->sTheList);
		}
	}
}
