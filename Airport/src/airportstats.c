/**************************************************************************
 File name:  airport.c
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Implementation of the AirportStats structure
 *************************************************************************/

#include "../include/airportstats.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char gszAStatsErrors[NUMBER_OF_ASTATS_ERRORS][MAX_ERROR_ASTATS_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszAStatsErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	astatsLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void astatsLoadErrorMessages ()
{
	LOAD_ASTATS_ERRORS
}

/**************************************************************************
 Function: 	 	astatsCreate

 Description: Initializes the statistic values

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsCreate (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsCreate", ERROR_NO_ASTATS_CREATE);
	}

	psAStats->numCrashes =
			psAStats->numEmergencyLandings =
					psAStats->numLandingPlanes =
							psAStats->numTakeoffPlanes =
									psAStats->totalFlyingTimeRemaining =
											psAStats->totalLandingTime =
													psAStats->totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	airportTerminate

 Description: Terminates the statistic values

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsTerminate (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("airportTerminate", ERROR_NO_ASTATS_TERMINATE);
	}

	psAStats->numCrashes =
			psAStats->numEmergencyLandings =
					psAStats->numLandingPlanes =
							psAStats->numTakeoffPlanes =
									psAStats->totalFlyingTimeRemaining =
											psAStats->totalLandingTime =
													psAStats->totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	astatsIncrementNumLandings

 Description: Increments numLandingPlanes by one

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsIncrementNumLandings (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsIncrementNumLandings", ERROR_INVALID_ASTATS);
	}
	psAStats->numLandingPlanes++;
}

/**************************************************************************
 Function: 	 	astatsIncrementNumTakeoffs

 Description: Increments numTakeoffPlanes by one

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsIncrementNumTakeoffs (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsIncrementNumTakeoffs", ERROR_INVALID_ASTATS);
	}
	psAStats->numTakeoffPlanes++;
}

/**************************************************************************
 Function: 	 	astatsIncrementEmergencies

 Description: Increments numEmergencyLandings by one

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsIncrementEmergencies (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsIncrementEmergencies", ERROR_INVALID_ASTATS);
	}
	psAStats->numEmergencyLandings++;
}

/**************************************************************************
 Function: 	 	astatsIncrementCrashes

 Description: Increments numEmergencyLandings by one

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsIncrementCrashes (AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsIncrementCrashes", ERROR_INVALID_ASTATS);
	}
	psAStats->numCrashes++;
}

/**************************************************************************
 Function: 	 	astatsAddTakeoffTime

 Description: Adds to the totalTakeoffTime

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsAddTakeoffTime (AirportStatsPtr psAStats, const int time)
{
	if (NULL == psAStats)
	{
		processError ("astatsAddTakeoffTime", ERROR_INVALID_ASTATS);
	}
	psAStats->totalTakeoffTime += time;
}

/**************************************************************************
 Function: 	 	astatsAddLandingTime

 Description: Adds to the totalTakeoffTime

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsAddLandingTime (AirportStatsPtr psAStats, const int time)
{
	if (NULL == psAStats)
	{
		processError ("astatsAddLandingTime", ERROR_INVALID_ASTATS);
	}
	psAStats->totalLandingTime += time;
}

/**************************************************************************
 Function: 	 	astatsAddFlyingTimeRemaining

 Description: Adds to the totalTakeoffTime

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	None
 *************************************************************************/
void astatsAddFlyingTimeRemaining (AirportStatsPtr psAStats, const int time)
{
	if (NULL == psAStats)
	{
		processError ("astatsAddFlyingTimeRemaining", ERROR_INVALID_ASTATS);
	}
	psAStats->totalFlyingTimeRemaining += time;
}

/**************************************************************************
 Function: 	 	astatsAverageLandingTime

 Description: Return the average landing waiting time

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	The average landing waiting time
 *************************************************************************/
float astatsAverageLandingTime (const AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("airportAverageLandingTime", ERROR_INVALID_ASTATS);
	}

	return (float) psAStats->totalLandingTime
				 / psAStats->numLandingPlanes;
}

/**************************************************************************
 Function: 	 	astatsAverageTakeoffTime

 Description: Return the average takeoff waiting time

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	The average takeoff waiting time
 *************************************************************************/
float astatsAverageTakeoffTime (const AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsAverageTakeoffTime", ERROR_INVALID_ASTATS);
	}
	return (float) psAStats->totalTakeoffTime
				 / psAStats->numTakeoffPlanes;
}

/**************************************************************************
 Function: 	 	astatsAverageFlyingTimeRemaining

 Description: Return the average flying time remaining

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	The average flying time remaining
 *************************************************************************/
float astatsAverageFlyingTimeRemaining (const AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsAverageFlyingTimeRemaining", ERROR_INVALID_ASTATS);
	}
	return (float) psAStats->totalFlyingTimeRemaining
				 / psAStats->numLandingPlanes;
}

/**************************************************************************
 Function: 	 	astatsNumEmergencyLandings

 Description: Return the number of emergency landings

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	The number of emergency landings
 *************************************************************************/
int astatsNumEmergencyLandings (const AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsNumEmergencyLandings", ERROR_INVALID_ASTATS);
	}
	return psAStats->numEmergencyLandings;
}

/**************************************************************************
 Function: 	 	astatsNumCrashes

 Description: Return the number of crashes

 Parameters:	psAStats - pointer to the airportStats

 Returned:	 	The number of crashes
 *************************************************************************/
int astatsNumCrashes (const AirportStatsPtr psAStats)
{
	if (NULL == psAStats)
	{
		processError ("astatsNumCrashes", ERROR_INVALID_ASTATS);
	}
	return psAStats->numCrashes;
}
