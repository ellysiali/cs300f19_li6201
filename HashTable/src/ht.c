/**************************************************************************
 File name:  ht.c
 Author:     Ellysia Li
 Date:		   Nov 15, 2019
 Class:		   CS300
 Assignment: Hash Tables
 Purpose:    Implementation for a hash table structure
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/ht.h"
#include "../../GenericDynamicList/include/list.h"

char gszHTErrors[NUMBER_OF_HT_ERRORS][MAX_ERROR_HT_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszHTErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	htCreate

 Description: Initializes the hash table

 Parameters:	psHTable 				 - pointer to the hash table
 	 	 	 	 	 	 	pHashFunction 	 - function pointer to the hash function
 	 	 	 	 	 	 	pCompareFunction - function pointer to the compare function
 	 	 	 	 	 	 	pPrintFunction   - function pointer to the print function

 Returned:	 	None
 *************************************************************************/
void htCreate (HashTablePtr psHTable, UserFunction pHashFunction,
							 UserFunction pCompareFunction, UserFunction pPrintFunction)
{

}
// results: If HT can be created, then HT exists and is empty
//					otherwise, ERROR_NO_HT_CREATE

/**************************************************************************
 Function: 	 	htTerminate

 Description: Terminates the hash table, freeing all elements

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	None
 *************************************************************************/
void htTerminate (HashTablePtr psHTable)
{

}
// results: If HT can be terminated, then HT no longer exists and is empty
//				   otherwise, ERROR_NO_HT_TERMINATE

/**************************************************************************
 Function: 	 	htLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void htLoadErrorMessages ()
{
	LOAD_HT_ERRORS
	lstLoadErrorMessages ();
}

/**************************************************************************
 Function: 	 	htSize

 Description: Returns the size of the hash table (number of buckets)

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	size of table
 *************************************************************************/
int htSize (const HashTablePtr psHTable)
{
	return 0;
}
// results: Returns the number of buckets (size) of the hash table
// 					error code priority: ERROR_INVALID_HT if HT is NULL

/**************************************************************************
 Function: 	 	htIsEmpty

 Description: Returns whether the hash table is empty

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	true if the hash table is empty; false otherwise
 *************************************************************************/
bool htIsEmpty (const HashTablePtr psHTable)
{
	return true;
}
// results: If HT is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_HT

/**************************************************************************
 Function: 	 	htInsert

 Description: Inserts an element into the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to the data

 Returned:	 	true if the key is valid and inserted into the hash table;
 	 	 	 	 	 	 	false otherwise
 *************************************************************************/
bool htInsert (HashTablePtr psHTable, const void *pKey,
																			const void *pData)
{
	return true;
}
// requires:
// results: Insert the data and key into the hash table.
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR

/**************************************************************************
 Function: 	 	htDelete

 Description: Deletes an element from the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to return the data from

 Returned:	 	true if the key was found and deleted from the hash table;
 	 	 	 	 	 	 	false otherwise
 *************************************************************************/
bool htDelete (HashTablePtr psHTable, const void *pKey, void *pData)
{
	return true;
}
// requires: psHTable is not empty
// results: Remove the data and key from the hash table, returning the data
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//															 ERROR_EMPTY_HT

/**************************************************************************
 Function: 	 	htUpdate

 Description: Updates the data of an element in the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to the value to update with

 Returned:	 	true if the key was found and updated; false otherwise
 *************************************************************************/
bool htUpdate (HashTablePtr psHTable, const void *pKey,
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	const void *pData)
{
	return true;
}
// requires: psQueue is not empty
// results: Updates the data from a given key in the hash table
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//															 ERROR_EMPTY_HT

/**************************************************************************
 Function: 	 	htFind

 Description: Finds a key and its data from the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to return the data from

 Returned:	 	true if the key was found; false otherwise
 *************************************************************************/
bool htFind (HashTablePtr psHTable, const void *pKey, void *pData)
{
	return true;
}
// results: Find and return the data for a given key in the hash table
// 						error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//																 ERROR_EMPTY_HT

/**************************************************************************
 Function: 	 	htPrint

 Description: Debugging: print out all buckets and their elements

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	None
 *************************************************************************/
void htPrint (HashTablePtr psHTable)
{

}
// requires: psQueue is not empty
// results: Debugging purposes; print out each bucket and its chain;
//					if the chain is empty, print out NULL
// 						error code priority: ERROR_INVALID_Q, ERROR_EMPTY_HT
