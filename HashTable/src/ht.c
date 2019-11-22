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
 	 	 	 	 	 	 	arraySize				 - size of the array
 	 	 	 	 	 	 	keySize					 - size of the data type of the key
 	 	 	 	 	 	 	dataSize				 - size of the data type of the data

 Returned:	 	None
 *************************************************************************/
void htCreate (HashTablePtr psHTable, HashFunction pHashFunction,
							 CompareFunction pCompareFunction, PrintFunction pPrintFunction,
							 const int arraySize, const int keySize, const int dataSize)
{
	int i;
	if (NULL == psHTable)
	{
		processError ("htCreate", ERROR_NO_HT_CREATE);
	}
	if (NULL == pHashFunction || NULL == pCompareFunction ||
			NULL == pPrintFunction)
	{
		processError ("htCreate", ERROR_NULL_HT_PTR);
	}
	psHTable->keySize = keySize;
	psHTable->dataSize = dataSize;
	psHTable->tableSize = arraySize;
	psHTable->psLists = (ListPtr) malloc (sizeof (List) * arraySize);

	for (i = 0; arraySize > i; i++)
	{
		lstCreate (&psHTable->psLists[i]);
	}

	psHTable->pCompareFunction = pCompareFunction;
	psHTable->pHashFunction = pHashFunction;
	psHTable->pPrintFunction = pPrintFunction;
}

/**************************************************************************
 Function: 	 	htTerminate

 Description: Terminates the hash table, freeing all elements

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	None
 *************************************************************************/
void htTerminate (HashTablePtr psHTable)
{
	int i;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htTerminate", ERROR_NO_HT_TERMINATE);
	}
	for (i = 0; psHTable->tableSize > i; i++)
	{
		while (!lstIsEmpty (&psHTable->psLists[i]))
		{
			lstFirst (&psHTable->psLists[i]);
			lstDeleteCurrent (&psHTable->psLists[i], &sTempHTE,
												sizeof (HashTableElement));
			free (sTempHTE.pData);
			free (sTempHTE.pKey);
		}
	}

	free (psHTable->psLists);
	psHTable->psLists = NULL;
	psHTable->pCompareFunction = NULL;
	psHTable->pHashFunction = NULL;
	psHTable->pPrintFunction = NULL;
	psHTable->tableSize = psHTable->keySize = psHTable->dataSize = 0;
}

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
	if (NULL == psHTable)
	{
		processError ("htSize", ERROR_INVALID_HT);
	}
	return psHTable->tableSize;
}

/**************************************************************************
 Function: 	 	htIsEmpty

 Description: Returns whether the hash table is empty

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	true if the hash table is empty; false otherwise
 *************************************************************************/
bool htIsEmpty (const HashTablePtr psHTable)
{
	int i;
	if (NULL == psHTable)
	{
		processError ("htIsEmpty", ERROR_INVALID_HT);
	}
	if (NULL == psHTable->psLists)
	{
		return true;
	}
	for (i = 0; psHTable->tableSize > i; i++)
	{
		if (!lstIsEmpty (&psHTable->psLists[i]))
		{
			return false;
		}
	}
	return true;
}

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
	int bucket;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htInsert", ERROR_INVALID_HT);
	}
	if (NULL == pKey || NULL == pData)
	{
		processError ("htInsert", ERROR_NULL_HT_PTR);
	}
	bucket = psHTable->pHashFunction (pKey);

	// Inserting when list is empty

	if (lstIsEmpty (&psHTable->psLists[bucket]))
	{
		sTempHTE.pKey = malloc (psHTable->keySize);
		sTempHTE.pData = malloc (psHTable->dataSize);
		memcpy (sTempHTE.pKey, pKey, psHTable->keySize);
		memcpy (sTempHTE.pData, pData, psHTable->dataSize);
		lstInsertBefore (&psHTable->psLists[bucket], &sTempHTE,
										 sizeof (HashTableElement));
		return true;
	}

	// Inserting when new element should be at the end

	lstLast (&psHTable->psLists[bucket]);
	lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));
	if (0 < psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		sTempHTE.pKey = malloc (psHTable->keySize);
		sTempHTE.pData = malloc (psHTable->dataSize);
		memcpy (sTempHTE.pKey, pKey, psHTable->keySize);
		memcpy (sTempHTE.pData, pData, psHTable->dataSize);
		lstInsertAfter (&psHTable->psLists[bucket], &sTempHTE,
				sizeof(HashTableElement));
		return true;
	}

	// Inserting in any other situation

	lstFirst (&psHTable->psLists[bucket]);
	lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));

	while (lstHasNext (&psHTable->psLists[bucket]) &&
				 0 < psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		lstNext (&psHTable->psLists[bucket]);
		lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));
	}
	if (0 == psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		return false;
	}

	sTempHTE.pKey = malloc (psHTable->keySize);
	sTempHTE.pData = malloc (psHTable->dataSize);
	memcpy (sTempHTE.pKey, pKey, psHTable->keySize);
	memcpy (sTempHTE.pData, pData, psHTable->dataSize);
	lstInsertBefore (&psHTable->psLists[bucket], &sTempHTE,
			sizeof(HashTableElement));

	return true;
}

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
	int bucket;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htDelete", ERROR_INVALID_HT);
	}
	if (NULL == pKey || NULL == pData)
	{
		processError ("htDelete", ERROR_NULL_HT_PTR);
	}
	bucket = psHTable->pHashFunction (pKey);

	if (lstIsEmpty (&psHTable->psLists[bucket]))
	{
		return false;
	}

	lstFirst (&psHTable->psLists[bucket]);
	lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof (HashTableElement));

	while (lstHasNext (&psHTable->psLists[bucket]) &&
				 0 < psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		lstNext (&psHTable->psLists[bucket]);
		lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));
	}
	if (0 == psHTable->pCompareFunction (pKey, sTempHTE.pKey))
			{
				lstDeleteCurrent (&psHTable->psLists[bucket], &sTempHTE,
												  sizeof (HashTableElement));
				memcpy (pData, sTempHTE.pData, psHTable->dataSize);
				free (sTempHTE.pData);
				free (sTempHTE.pKey);
				return true;
			}
	return false;
}

/**************************************************************************
 Function: 	 	htUpdate

 Description: Updates the data of an element in the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to the value to update with
when new element should be at the end
 Returned:	 	true if the key was found and updated; false otherwise
 *************************************************************************/
bool htUpdate (HashTablePtr psHTable, const void *pKey,
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	const void *pData)
{
	int bucket;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htUpdate", ERROR_INVALID_HT);
	}
	if (NULL == pKey || NULL == pData)
	{
		processError ("htUpdate", ERROR_NULL_HT_PTR);
	}
	bucket = psHTable->pHashFunction (pKey);

	if (lstIsEmpty (&psHTable->psLists[bucket]))
	{
		return false;
	}

	lstFirst (&psHTable->psLists[bucket]);
	lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof (HashTableElement));

	while (lstHasNext (&psHTable->psLists[bucket]) &&
				 0 < psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		lstNext (&psHTable->psLists[bucket]);
		lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));
	}
	if (0 == psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		memcpy (sTempHTE.pData, pData, psHTable->dataSize);
		lstUpdateCurrent (&psHTable->psLists[bucket], &sTempHTE,
											sizeof (HashTableElement));
		return true;
	}
	return false;
}

/**************************************************************************
 Function: 	 	htFind

 Description: Finds a key and its data from the hash table

 Parameters:	psHTable - pointer to the hash table
 	 	 	 	 	 	  pKey     - pointer to the key
 	 	 	 	 	 	  pData    - pointer to return the data from

 Returned:	 	true if the key was found; false otherwise
 *************************************************************************/
bool htFind (const HashTablePtr psHTable, const void *pKey, void *pData)
{
	int bucket;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htFind", ERROR_INVALID_HT);
	}
	if (NULL == pKey || NULL == pData)
	{
		processError ("htFind", ERROR_NULL_HT_PTR);
	}
	bucket = psHTable->pHashFunction (pKey);

	if (lstIsEmpty (&psHTable->psLists[bucket]))
	{
		return false;
	}

	lstFirst (&psHTable->psLists[bucket]);
	lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof (HashTableElement));

	while (lstHasNext (&psHTable->psLists[bucket]) &&
				 0 < psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		lstNext (&psHTable->psLists[bucket]);
		lstPeek (&psHTable->psLists[bucket], &sTempHTE, sizeof(HashTableElement));
	}
	if (0 == psHTable->pCompareFunction (pKey, sTempHTE.pKey))
	{
		memcpy (pData, sTempHTE.pData, psHTable->dataSize);
		return true;
	}
	return false;
}

/**************************************************************************
 Function: 	 	htPrint

 Description: Debugging: print out all buckets and their elements

 Parameters:	psHTable - pointer to the hash table

 Returned:	 	None
 *************************************************************************/
void htPrint (const HashTablePtr psHTable)
{
	int i = 0;
	HashTableElement sTempHTE;
	if (NULL == psHTable)
	{
		processError ("htPrint", ERROR_INVALID_HT);
	}
	for (i = 0; psHTable->tableSize > i; i++)
	{
		printf ("Bucket %d: ", i);

		if (lstIsEmpty (&psHTable->psLists[i]))
		{
			printf ("NULL");
		}
		else
		{
			lstFirst (&psHTable->psLists[i]);
		}
		while (lstHasCurrent (&psHTable->psLists[i]))
		{
			lstPeek (&psHTable->psLists[i], &sTempHTE, sizeof (HashTableElement));
			psHTable->pPrintFunction (sTempHTE.pKey, sTempHTE.pData);
			printf (" ");
			lstNext (&psHTable->psLists[i]);
		}
		puts ("");
	}
}
