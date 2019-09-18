/**************************************************************************
 File name:  list.c
 Author:     Ellysia Li
 Date:			 9.17.2019
 Class:			 CS300
 Assignment: GenericDynamicList
 Purpose:    Implementation for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

//char gszErrors[LIST_NUMBER_OF_ERRORS][LIST_MAX_ERROR_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
//	printf ("Function: %s %s \n ", pszFunctionName, gszErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	stkLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void stkLoadErrorMessages ()
{
//	LOAD_ERRORS
}
