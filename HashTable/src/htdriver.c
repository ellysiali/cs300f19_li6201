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

#define STRING_HASH_SIZE 1
#define INT_HASH_SIZE 256
#define MASK 0x000ff000
#define SHIFT 12
#define MAX_STRING_SIZE 9

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success (char *pszStr)
{
	printf ("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message and exit the program

 Parameters:	pszStr - the message to print

 Returned:	 	none

 ****************************************************************************/
static void failure (char *pszStr)
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

 Parameters:		pKey  - pointer to the (string) key

 Returned:	 		none
 ****************************************************************************/
static int stringHash (const void* pKey)
{
	const int MULTIPLIER = 31;
	int i, key = 1;

	for (i = 0; MAX_STRING_SIZE > i; i++)
	{
		key = key * MULTIPLIER + *(char*) pKey + i;
	}
	return abs(key) % STRING_HASH_SIZE;
}

/****************************************************************************
 Function: 	 		midSquareHash

 Description: 	a midsquare hashing function to test the driver with

 Parameters:		pKey  - pointer to the (int) key

 Returned:	 		none
 ****************************************************************************/
static int midSquareHash (const void* pKey)
{
	return (*(uint64_t*) pKey) * (*(uint64_t*) pKey) & MASK >> SHIFT;
}

/****************************************************************************
 Function: 	 		compareString

 Description: 	a string comparing function to test the driver with

 Parameters:		pKey  - pointer to the (string) key
 	 	 	 	 	 	 	 	pOtherKey - pointer to the other (string) key

 Returned:	 		none
 ****************************************************************************/
static bool compareString (const void* pKey, const void* pOtherKey)
{
	return 0 == strncmp ((char*) pKey, (char*) pOtherKey, MAX_STRING_SIZE);
}

/****************************************************************************
 Function: 	 		compareInt

 Description: 	an int comparing function to test the driver with

 Parameters:		pKey  - pointer to the (int) key
 	 	 	 	 	 	 	 	pOtherKey - pointer to the other (int) key

 Returned:	 		none
 ****************************************************************************/
static bool compareInt (const void* pKey, const void* pOtherKey)
{
	return *(int*) pKey == *(int*) pOtherKey;
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
	printf ("%s-%d", (char*) pKey, *(int*) pData);
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
	printf ("%d-%f", *(int*) pKey, *(float*) pData);
}

/**************************************************************************
 Function: 	 	main"String HT is correct size"

 Description: test all the functionality of the hash table

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	const char WORD1[] = "Red", WORD2[] = "Orange";
	HashTable sTheHTable;
	char szKey[MAX_STRING_SIZE];
	int i = 0, intBuffer;
	float k;

	puts ("Driver Start\n");

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
					"Element inserted into empty bucket",
					"Element NOT inserted into empty bucket");
	assert (!htIsEmpty (&sTheHTable),
					"Hash table is not empty",
					"Hash table IS empty");

	strncpy (szKey, WORD2, MAX_STRING_SIZE);
	i++;
	assert (htInsert (&sTheHTable, &szKey, &i),
					"Element inserted into nonempty bucket",
					"Element NOT inserted into nonempty bucket");
	assert (!htIsEmpty (&sTheHTable),
					"Hash table is not empty",
					"Hash table IS empty");

	htPrint (&sTheHTable);
	puts ("");

	// Validate htInsert will NOT add an element if it has a pre-existing key

	assert (!htInsert (&sTheHTable, &szKey, &i),
					"Pre-existing element was not inserted into hash table",
					"Pre-existing element WAS inserted into hash table");
	puts ("");

	// Validate htFind with a valid key

	assert (htFind (&sTheHTable, &szKey, &intBuffer),
					"Key was found in the hash table",
					"Key was NOT found in the hash table");
	puts ("");

	assert (i == intBuffer, "Found (peeked) data is correct",
													"Found (peeked) data is NOT correct");

	// Validate htDelete with a valid key

	assert (htDelete (&sTheHTable, &szKey, &i),
					"Element deleted from hash table",
					"Element NOT deleted from hash table");

	assert (i == intBuffer, "Deleted data is correct",
													"Deleted data is NOT correct");
	puts ("");

	// Validate htFind with an invalid key

	assert (!htFind (&sTheHTable, &szKey, &intBuffer),
					"Non-existent key was not found in the hash table",
					"Non-existent key WAS found in the hash table");
	htPrint (&sTheHTable);
	puts ("");

	// Validate htDelete with an invalid key

	assert (!htDelete (&sTheHTable, &szKey, &i),
					"Non-existent element was not deleted from hash table",
					"Non-existent element WAS deleted from hash table");
	puts ("");

	// Validate a fully deleted hash table is empty and htDelete when empty

	i--;
	strncpy (szKey, WORD1, MAX_STRING_SIZE);
	htDelete (&sTheHTable, &szKey, &i);

	assert (htIsEmpty (&sTheHTable), "Fully deleted hash table is empty",
																   "Fully deleted hash table is NOT empty");
	htPrint (&sTheHTable);

	htTerminate (&sTheHTable);

	// Validate the hash table using a lot more elements and a larger table
	// (using int keys and float data this time)

	htCreate (&sTheHTable, midSquareHash, compareInt, printInt,
						INT_HASH_SIZE, sizeof (int), sizeof (float));



	htTerminate (&sTheHTable);

	puts ("\nDriver End");

	return EXIT_SUCCESS;
}




