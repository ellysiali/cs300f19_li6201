/**************************************************************************
 File name:  queue.c
 Author:     Ellysia Li
 Date:		 	 Oct 20, 2019
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    Implementation of a Generic Queue backed by a existing Priority
 	 	 	 	 	 	 Queue
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"

char gszQErrors[NUMBER_OF_Q_ERRORS][MAX_ERROR_Q_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	queueCreate

 Description: Initializes the list in the queue

 Parameters:	psQueue - pointer to the queue

 Returned:	 	None
 *************************************************************************/
void queueCreate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueCreate", ERROR_NO_Q_CREATE);
	}
	pqueueCreate (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueTerminate

 Description: Terminates the list as well as the data in the queue elements

 Parameters:	psQueue - pointer to the queue

 Returned:	 	None
 *************************************************************************/
void queueTerminate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueCreate", ERROR_NO_Q_TERMINATE);
	}
	pqueueTerminate (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void queueLoadErrorMessages ()
{
	pqueueLoadErrorMessages ();
	LOAD_Q_ERRORS
}

/**************************************************************************
 Function: 	 	queueSize

 Description: Returns the size of the queue

 Parameters:	psQueue - pointer to the queue

 Returned:	 	Size of the queue
 *************************************************************************/
int queueSize (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueSize", ERROR_INVALID_Q);
	}
	return pqueueSize (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueIsEmpty

 Description: Checks if the queue is empty

 Parameters:	psQueue - pointer to the queue

 Returned:	 	True if queue is empty otherwise false
 *************************************************************************/
bool queueIsEmpty (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueIsEmpty", ERROR_INVALID_Q);
	}
	return pqueueIsEmpty (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueEnqueue

 Description: Adds a value to the start of the queue

 Parameters:	psQueue  - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer  - pointer to value
 	 	 	 	 	 	 	size     - size of value

 Returned:	 	None
 *************************************************************************/
void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	const int PRIORITY = 0;

	if (NULL == psQueue)
	{
		processError ("queueEnqueue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queueEnqueue", ERROR_NULL_Q_PTR);
	}
	pqueueEnqueue (&psQueue->sTheQueue, pBuffer, size, PRIORITY);
}

/**************************************************************************
 Function: 	 	queueDequeue

 Description: Removes the (oldest) value at the end of the queue

 Parameters:	psQueue   - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer   - pointer to store the removed value
 	 	 	 	 	 	 	size      - size of the removed value

 Returned:	 	Pointer to the buffer of the removed value
 *************************************************************************/
void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	int priorityBuffer;

	if (NULL == psQueue)
	{
		processError ("queueDequeue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queueDequeue", ERROR_NULL_Q_PTR);
	}
	if (queueIsEmpty (psQueue))
	{
		processError ("queueDequeue", ERROR_EMPTY_Q);
	}
	pqueueDequeue (&psQueue->sTheQueue, pBuffer, size, &priorityBuffer);
	return pBuffer;
}

/**************************************************************************
 Function: 	 	queuePeek

 Description: Peek at the first value's data of the queue

 Parameters:	psQueue  - pointer to the priority queue
 	 	 	 	 	 	 	pBuffer  - pointer to store the peeked value
 	 	 	 	 	 	 	size     - size of the peeked value

 Returned:	 	Pointer to the buffer of the peeked value
 *************************************************************************/
void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	int priorityBuffer;

	if (NULL == psQueue)
	{
		processError ("queuePeek", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queuePeek", ERROR_NULL_Q_PTR);
	}
	if (queueIsEmpty (psQueue))
	{
		processError ("queuePeek", ERROR_EMPTY_Q);
	}
	pqueuePeek (&psQueue->sTheQueue, pBuffer, size, &priorityBuffer);
	return pBuffer;
}
