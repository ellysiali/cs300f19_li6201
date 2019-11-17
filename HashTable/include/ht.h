/**************************************************************************
 File name:  ht.h
 Author:     Ellysia Li
 Date:		   Nov 15, 2019
 Class:		   CS300
 Assignment: Hash Tables
 Purpose:    This file defines the constants, data structures, and
             function prototypes for implementing a hash table
 *************************************************************************/

#ifndef HT_H_
#define HT_H_

#include <stdlib.h>
#include <stdbool.h>
#include "../../GenericDynamicList/include/list.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_HT_CHARS 64

enum {NO_HT_ERROR = 0,
			ERROR_NO_HT_CREATE,
			ERROR_NO_HT_TERMINATE,
			ERROR_INVALID_HT,
			ERROR_FULL_HT,
			ERROR_NULL_HT_PTR,
			ERROR_EMPTY_HT}; // If this error name changes, change statement below
#define NUMBER_OF_HT_ERRORS ERROR_EMPTY_HT - NO_HT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_HT_ERRORS strcpy(gszHTErrors[NO_HT_ERROR], "No Error.");\
strcpy(gszHTErrors[ERROR_NO_HT_CREATE], "Error: No Hash Table Create.");\
strcpy(gszHTErrors[ERROR_NO_HT_TERMINATE], "Error: No Hash Table Terminate.");\
strcpy(gszHTErrors[ERROR_INVALID_HT], "Error: Invalid Hash Table.");\
strcpy(gszHTErrors[ERROR_FULL_HT], "Error: Full Hash Table.");\
strcpy(gszHTErrors[ERROR_NULL_HT_PTR], "Error: NULL Pointer.");\
strcpy(gszHTErrors[ERROR_EMPTY_HT], "Error: Empty Hash Table.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct HashTable *HashTablePtr;

typedef int (*HashFunction) (const void*);
typedef bool (*CompareFunction) (const void*, const void*);
typedef void (*PrintFunction) (const void*, const void*);

typedef struct HashTable
{
	ListPtr psLists;
	int tableSize;
	HashFunction pHashFunction;
	CompareFunction pCompareFunction;
	PrintFunction pPrintFunction;
} HashTable;

typedef struct HashTableElement
{
	void* pKey;
	void* pData;
} HashTableElement;

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void htCreate (HashTablePtr psHTable, HashFunction pHashFunction,
										  CompareFunction pCompareFunction,
											PrintFunction pPrintFunction, const int size);
// results: If HT can be created, then HT exists and is empty
//					otherwise, ERROR_NO_HT_CREATE

extern void htTerminate (HashTablePtr psHTable);
// results: If HT can be terminated, then HT no longer exists and is empty
//				   otherwise, ERROR_NO_HT_TERMINATE

extern void htLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*									Checking the data in the hash table
**************************************************************************/
extern int htSize (const HashTablePtr psHTable);
// results: Returns the number of buckets (size) of the hash table
// 					error code priority: ERROR_INVALID_HT if HT is NULL

extern bool htIsEmpty (const HashTablePtr psHTable);
// results: If HT is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_HT

/**************************************************************************
*									Inserting, retrieving,and updating values
**************************************************************************/
extern bool htInsert (HashTablePtr psHTable, const void *pKey,
																						 const void *pData);
// requires:
// results: Insert the data and key into the hash table.
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR

extern bool htDelete (HashTablePtr psHTable, const void *pKey, void *pData);
// requires: psHTable is not empty
// results: Remove the data and key from the hash table, returning the data
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//															 ERROR_EMPTY_HT

extern bool htUpdate (HashTablePtr psHTable, const void *pKey,
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 const void *pData);
// requires: psQueue is not empty
// results: Updates the data from a given key in the hash table
//					error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//															 ERROR_EMPTY_HT

/**************************************************************************
*													Peek and Print Operations
**************************************************************************/
extern bool htFind (HashTablePtr psHTable, const void *pKey, void *pData);
// results: Find and return the data for a given key in the hash table
// 						error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//																 ERROR_EMPTY_HT

extern void htPrint (HashTablePtr psHTable);
// requires: psQueue is not empty
// results: Debugging purposes; print out each bucket and its chain;
//					if the chain is empty, print out NULL
// 						error code priority: ERROR_INVALID_Q, ERROR_EMPTY_HT

#endif /* HT_H_ */
