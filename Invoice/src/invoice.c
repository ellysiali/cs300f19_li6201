/**************************************************************************
 File name:  invoice.c
 Author:     Ellysia Li
 Date:		   Nov 15, 2019
 Class:		   CS300
 Assignment: Hash Tables
 Purpose:    Implementation for an invoice program
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../HashTable/include/ht.h"

#define STRING_HASH_SIZE 50
#define INT_HASH_SIZE 256
#define MASK 0x000ff000
#define SHIFT 12
#define MAX_STRING_SIZE 21
#define NUMBER_OF_FILES 3
#define CURRENCY 1
#define ITEM 2
#define ACTION 3

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
	return ((*(uint64_t*) pKey) * (*(uint64_t*) pKey)) & MASK >> SHIFT;
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
	printf ("%s: %.2f ", (char*) pKey, *(float*) pData);
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
	printf ("%d, %s ", *(int*) pKey, (char*) pData);
}

/**************************************************************************
 Function: 	 	main

 Description: Run the invoice program

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main (int argc, char* argv[])
{
	int i, count, id, quantity;
	char szDenom[MAX_STRING_SIZE], szName[MAX_STRING_SIZE],
			 szManufacturer[MAX_STRING_SIZE], szConcat[MAX_STRING_SIZE];
	float cost;
	HashTable sCurrencyTable, sItemTable;
	FILE* pInFile = NULL;

  // Check number of arguments

  if ( argc != NUMBER_OF_FILES + 1)
  {
    printf ("Invalid number of arguments\n");
    return EXIT_FAILURE;
  }

  // Check valid files
  for (i = 1; NUMBER_OF_FILES > i; i++)
	{
		pInFile = fopen (argv[i], "r");
		if (NULL == pInFile)
		{
			printf ("Could not open file\n");
			return EXIT_FAILURE;
		}
	}

  htLoadErrorMessages ();
	htCreate (&sCurrencyTable, stringHash, compareString, printString,
						STRING_HASH_SIZE, sizeof (char) * MAX_STRING_SIZE, sizeof (float));
	htCreate (&sItemTable, midSquareHash, compareInt, printInt,
						INT_HASH_SIZE, sizeof (int), sizeof (char) * MAX_STRING_SIZE);

  // Implement currency hash table

	pInFile = fopen (argv[CURRENCY], "r");
	count = fscanf (pInFile, "%s %f", szDenom, &cost);
	while (0 < count)
	{
		htInsert (&sCurrencyTable, &szDenom, &cost);
		count = fscanf (pInFile, "%s %f", szDenom, &cost);
	}

	// Implement item hash table

	pInFile = fopen (argv[ITEM], "r");
	count = fscanf (pInFile, "%d %s %s", &id, szName, szManufacturer);
	while (0 < count)
	{
		sprintf (szConcat, "%s, %s", szName, szManufacturer);
		htInsert (&sItemTable, &id, szConcat);
		count = fscanf (pInFile, "%d %s %s", &id, szName, szManufacturer);
	}

	// Print purchases to file
	pInFile = fopen (argv[ACTION], "r");
	count = fscanf (pInFile, "%d %d %f %s", &id, &quantity, &cost, szDenom);
	while (0 < count)
	{
		// Actually add implementation for writing to file
		// Actually get correct name/manufacturer and prices in USD
		printf ("%d %s, %d %.2f %.2f\n", id, szManufacturer, quantity, cost, cost);
		count = fscanf (pInFile, "%d %d %f %s", &id, &quantity, &cost, szDenom);
	}

	htTerminate (&sCurrencyTable);
	htTerminate (&sItemTable);

  fclose (pInFile);

	return EXIT_SUCCESS;
}
