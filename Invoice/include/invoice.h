/**************************************************************************
 File name:  invoice.h
 Author:     Ellysia Li
 Date:		   Nov 15, 2019
 Class:		   CS300
 Assignment: Hash Tables
 Purpose:    This file defines the constants, data structures, and
             function prototypes for implementing an invoice
 *************************************************************************/

#ifndef INVOICE_H_
#define INVOICE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "../../HashTable/include/ht.h"

typedef struct Invoice *InvoicePtr;

typedef struct Invoice
{
	HashTable sConversionTable, sItemTable;
	Queue sPurchases;
} Invoice;

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
											PrintFunction pPrintFunction, const int arraySize,
											const int keySize, const int dataSize);
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
extern bool htFind (const HashTablePtr psHTable, const void *pKey, void *pData);
// results: Find and return the data for a given key in the hash table
// 						error code priority: ERROR_INVALID_HT, ERROR_NULL_HT_PTR,
//																 ERROR_EMPTY_HT

extern void htPrint (const HashTablePtr psHTable);
// requires: psQueue is not empty
// results: Debugging purposes; print out each bucket and its chain;
//					if the chain is empty, print out NULL
// 						error code priority: ERROR_INVALID_Q, ERROR_EMPTY_HT

#endif /* INVOICE_H_ */
