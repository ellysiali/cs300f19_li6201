/**************************************************************************
 File name:  htdriver.c
 Author:     Ellysia Li
 Date:		   Nov 15, 2019
 Class:		   CS300
 Assignment: Hash Tables
 Purpose:    Testing for a hash table structure
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/ht.h"
#include "../../GenericDynamicList/include/list.h"

#define STRING_HASH_SIZE 1
#define INT_HASH_SIZE 256
#define MASK 0x000ff000
#define SHIFT 12
#define MAX_STRING_SIZE 21
#define LONG_INSERT_SIZE 10000

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success (const char *pszStr)
{
	printf ("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message and exit the program

 Parameters:	pszStr - the message to print

 Returned:	 	none

 ****************************************************************************/
static void failure (const char *pszStr)
{
	printf ("FAILURE: %s\n", pszStr);
	exit (EXIT_FAILURE);
}

/****************************************************************************
 Function: 	 		assert

 Description: 	if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	  failure

 Parameters:		szStr - the message to print

 Returned:	 		none
 ****************************************************************************/
static void assert (bool bExpression, const char *pTrue, const char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

/****************************************************************************
 Function: 	 		stringHash

 Description: 	a string hashing function to test the driver with

 Parameters:		pKey - pointer to the (string) key

 Returned:	 		the bucket of the respective key
 ****************************************************************************/
static int stringHash (const void* pKey)
{
	const int MULTIPLIER = 31;
	int i, bucket = 1;

	for (i = 0; MAX_STRING_SIZE > i; i++)
	{
		bucket = bucket * MULTIPLIER + *(char*) pKey + i;
	}
	return abs(bucket) % STRING_HASH_SIZE;
}

/****************************************************************************
 Function: 	 		midSquareHash

 Description: 	a midsquare hashing function to test the driver with

 Parameters:		pKey  - pointer to the (int) key

 Returned:	 		the bucket of the respective key
 ****************************************************************************/
static int midSquareHash (const void* pKey)
{
	return (((*(uint64_t*) pKey) * (*(uint64_t*) pKey)) & MASK) >> SHIFT;
}

/****************************************************************************
 Function: 	 		compareString

 Description: 	a string comparing function to test the driver with

 Parameters:		pKey  - pointer to the (string) key
 	 	 	 	 	 	 	 	pOtherKey - pointer to the other (string) key

 Returned:	 	  an int representative of the comparison (positive if inserted
 	 	 	 	 	 	 	 	after, negative if before, and zero if the same)
 ****************************************************************************/
static int compareString (const void* pKey, const void* pOtherKey)
{
	return strncmp ((char*) pKey, (char*) pOtherKey, MAX_STRING_SIZE);
}

/****************************************************************************
 Function: 	 		compareInt

 Description: 	an int comparing function to test the driver with

 Parameters:		pKey  - pointer to the (int) key
 	 	 	 	 	 	 	 	pOtherKey - pointer to the other (int) key

 Returned:	 		an int representative of the comparison (positive if inserted
 	 	 	 	 	 	 	 	after, negative if before, and zero if the same)
 ****************************************************************************/
static int compareInt (const void* pKey, const void* pOtherKey)
{
	return *(int*) pKey - *(int*) pOtherKey;
}


/****************************************************************************
 Function: 	 		printString

 Description: 	a string-int printing function to test the driver with

 Parameters:		pKey  - pointer to the (string) key
 	 	 	 	 	 	 	 	pData - pointer to the (int) data

 Returned:	 		none
 ****************************************************************************/
static void printString (const void* pKey, const void* pData)
{
	printf ("%s: %d ", (char*) pKey, *(int*) pData);
}

/****************************************************************************
 Function: 	 		printInt

 Description: 	an int-float printing function to test the driver with

 Parameters:		pKey  - pointer to the (int) key
 	 	 	 	 	 	 	 	pData - pointer to the (float) data

 Returned:	 		none
 ****************************************************************************/
static void printInt (const void* pKey, const void* pData)
{
	printf ("%d, %f ", *(int*) pKey, *(float*) pData);
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the hash table

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	const char WORD1[] = "Red", WORD2[] = "Orange";
	HashTable sTheHTable;
	HashTableElement sTemp;
	char szKey[MAX_STRING_SIZE];
	int i = 0, intBuffer;
	float j = 0, floatBuffer;

	puts ("Driver Start\n");
	htLoadErrorMessages ();

	// Validate htCreate

	htCreate (&sTheHTable, stringHash, compareString, printString,
						STRING_HASH_SIZE, sizeof (char) * MAX_STRING_SIZE, sizeof (int));

	assert (htIsEmpty (&sTheHTable), "Initiated hash table is empty",
																   "Initiated hash table is NOT empty");
	assert (STRING_HASH_SIZE == htSize (&sTheHTable),
					"String hash table is correct size",
					"String hash table is NOT correct size");
	htPrint (&sTheHTable);
	puts ("");

	// Validate htInsert works when adding to an empty/nonempty bucket

	strncpy (szKey, WORD1, MAX_STRING_SIZE);
	assert (htInsert (&sTheHTable, &szKey, &i),
					"htInsert returned true when inserting into empty bucket",
					"htInsert returned FALSE when inserting into empty bucket");
	assert (!htIsEmpty (&sTheHTable),
					"Hash table is not empty",
					"Hash table IS empty");

	strncpy (szKey, WORD2, MAX_STRING_SIZE);
	i++;
	assert (htInsert (&sTheHTable, &szKey, &i),
					"htInsert returned true when inserting valid key into nonempty "
					"bucket",
					"htInsert returned FALSE when inserting valid key into nonempty "
					"bucket");
	assert (!htIsEmpty (&sTheHTable),
					"Hash table is not empty",
					"Hash table IS empty");

	htPrint (&sTheHTable);
	puts ("");

	// Validate htInsert will NOT add an element if it has a pre-existing key

	assert (!htInsert (&sTheHTable, &szKey, &i),
					"htInsert returned false when inserting invalid key into bucket",
					"htInsert returned TRUE when inserting invalid key into bucket");
	puts ("");

	// Validate htFind and htDelete with a valid key

	assert (htFind (&sTheHTable, &szKey, &intBuffer),
					"Key was found in the hash table",
					"Key was NOT found in the hash table");

	assert (i == intBuffer, "Found (returned) data is correct",
													"Found (returned) data is NOT correct");

	assert (htDelete (&sTheHTable, &szKey, &i),
					"htDelete returned true when deleting valid key",
					"htDelete returned FALSE when deleting valid key");

	assert (i == intBuffer, "Deleted (returned) data is correct",
													"Deleted (returned) data is NOT correct");
	htPrint (&sTheHTable);
	puts ("");

	// Validate htFind and htDelete with an invalid key

	assert (!htFind (&sTheHTable, &szKey, &intBuffer),
					"Invalid key was not found in the hash table",
					"Invalid key WAS found in the hash table");

	assert (!htDelete (&sTheHTable, &szKey, &i),
					"htDelete returned false when deleting invalid key",
					"htDelete returned TRUE when deleting invalid key");
	puts ("");

	// Validate a fully deleted hash table is empty and htDelete when empty

	i--;
	strncpy (szKey, WORD1, MAX_STRING_SIZE);
	htDelete (&sTheHTable, &szKey, &i);
	assert (htIsEmpty (&sTheHTable), "Fully deleted hash table is empty",
																   "Fully deleted hash table is NOT empty");
	htPrint (&sTheHTable);

	puts ("");

	// Validate htFind and htDelete with an empty bucket

	assert (!htFind (&sTheHTable, &szKey, &intBuffer),
					"Invalid key was not found in the (empty) hash table",
					"Invalid key WAS found in the (empty) hash table");

	assert (!htDelete (&sTheHTable, &szKey, &i),
					"htDelete returned false when deleting invalid key",
					"htDelete returned TRUE when deleting invalid key");
	puts ("");


	htTerminate (&sTheHTable);

	// Validate the hash table using a lot more elements and an actual table
	// (using int keys and float data this time)

	htCreate (&sTheHTable, midSquareHash, compareInt, printInt,
						INT_HASH_SIZE, sizeof (int), sizeof (float));

	// Insert elements

	for (i = 0; i < LONG_INSERT_SIZE; i++)
	{
		intBuffer = i * i;
		htInsert (&sTheHTable, &intBuffer, &j);

		lstPeek (&(sTheHTable.psLists[midSquareHash (&intBuffer)]), &sTemp,
						 sizeof (HashTableElement));

		if (intBuffer != *(int*) sTemp.pKey || j != *(float*) sTemp.pData)
		{
			assert (intBuffer == *(int*) sTemp.pKey && j == *(float*) sTemp.pData,
					"Correct key/data inserted into hash table",
					"Incorrect key/data inserted into hash table");
		}
		j++;

	}

	// Update elements

	j = 1;
	for (i = 0; i < LONG_INSERT_SIZE; i++)
	{
		intBuffer = i * i;
		htUpdate (&sTheHTable, &intBuffer, &j);

		lstPeek (&(sTheHTable.psLists[midSquareHash (&intBuffer)]), &sTemp,
						 sizeof (HashTableElement));

		if (intBuffer != *(int*) sTemp.pKey || j != *(float*) sTemp.pData)
		{
			assert (intBuffer == *(int*) sTemp.pKey && j == *(float*) sTemp.pData,
					"Correct key/data updated",
					"Incorrect key/data updated");
		}
		j++;
	}

	// Find elements

	j = 1;
	for (i = 0; i < LONG_INSERT_SIZE; i++)
	{
		intBuffer = i * i;
		htFind (&sTheHTable, &intBuffer, &floatBuffer);

		if (j != floatBuffer)
		{
			assert (j != floatBuffer,
					"Correct data for key found",
					"Incorrect data for key found");
		}
		j++;
	}

	success ("Validated hash table functions for larger int-key, "
					 "float-data hash table");

	// Validate when terminating a non-empty hash table

	htTerminate (&sTheHTable);

	assert (htIsEmpty (&sTheHTable), "Terminated hash table is empty",
																   "Terminated hash table is NOT empty");

	puts ("\nDriver End");

	return EXIT_SUCCESS;
}




