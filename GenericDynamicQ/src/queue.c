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

void queueCreate (QueuePtr psQueue)
{

}
// results: If Q can be created, then Q exists and is empty
//					otherwise, ERROR_NO_Q_CREATE


void queueTerminate (QueuePtr psQueue)
{

}
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_Q_TERMINATE

void queueLoadErrorMessages ()
{

}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
int queueSize (const QueuePtr psQueue)
{
	return 0;
}
// results: Returns the number of elements in the Q
// 					error code priority: ERROR_INVALID_Q if Q is NULL

bool queueIsEmpty (const QueuePtr psQueue)
{
	return true;
}
// results: If Q is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_Q



/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/
void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{

}
// requires: psQueue is not full
// results: Insert the element into the FIFO queue.
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR

void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	return pBuffer;
}
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//															 ERROR_EMPTY_Q

/**************************************************************************
*													Peek Operations
**************************************************************************/
void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	return pBuffer;
}
// requires: psQueue is not empty
// results: The value of the first element is returned through the
//					argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//																 ERROR_EMPTY_Q
