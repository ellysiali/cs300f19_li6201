/**************************************************************************
 File name:  wordCountDriver.c
 Author:     Ellysia Li
 Date:		 	 Nov 10, 2019
 Class:		   CS300
 Assignment: Trees
 Purpose:    Implementation of a word counter
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

int main (int argc, char* argv[])
{
	int countBuffer;
	char szWord[WORD_MAX + 1];
	FILE* pInFile = NULL;
	TreeNodePtr psRoot;

	// Check number of arguments

	if (argc != 2)
	{
		printf ("Invalid number of arguments\n");
		return EXIT_FAILURE;
	}

  // Check valid file

	pInFile = fopen (argv[1], "r");

	if (NULL == pInFile)
	{
		printf ("Could not open file\n");
		return EXIT_FAILURE;
	}

	trLoadErrorMessages ();
	trCreate (&psRoot);

	while (!feof (pInFile))
	{
		fscanf (pInFile, "%s", szWord);
		if (!trInsert (&psRoot, szWord, 1))
		{
			trFind (psRoot, szWord, &countBuffer);
			trUpdate (psRoot, szWord, countBuffer + 1);
		}
	}

	trPrintInOrder (psRoot);

	trTerminate (&psRoot);

	return EXIT_SUCCESS;
}
