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

#define STRING_HASH_SIZE 7
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
	return (*(int*) pKey) * (*(int*) pKey) & MASK >> SHIFT;
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
	return 0 == strncmp (pKey, pOtherKey, MAX_STRING_SIZE);
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
	HashTable sTheHTable;
	char szArray[MAX_STRING_SIZE], i, word[] = "B";
	int j;
	float k;

	puts ("Driver Start\n");

	htCreate (&sTheHTable, stringHash, compareString, printString,
						STRING_HASH_SIZE);

	assert (htIsEmpty (&sTheHTable), "Initiated HT is empty",
																   "Initiated HT is NOT empty");
	assert (STRING_HASH_SIZE == htSize (&sTheHTable),
					"String HT is correct size",
					"String HT is NOT correct size");

	i = 'A';
	memset (szArray, '\0', MAX_STRING_SIZE);
	strncpy (szArray, &i, MAX_STRING_SIZE);
	j = 0;

	htInsert (&sTheHTable, &szArray, &j);

	memset (szArray, '\0', MAX_STRING_SIZE);
	strncpy (szArray, word, MAX_STRING_SIZE);
	j = 2;

	// Issues with inserting - trying to use memcpy but don't know the size of
	// pData nor pKey
	htInsert (&sTheHTable, &szArray, &j);

	htPrint (&sTheHTable);

	htTerminate (&sTheHTable);

	puts ("End");

	return EXIT_SUCCESS;
}




