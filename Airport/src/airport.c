/**************************************************************************
 File name:  airport.c
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Implementation of an Airport Simulator
 *************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/airport.h"
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"

char gszAirportErrors[NUMBER_OF_AIRPORT_ERRORS][MAX_ERROR_AIRPORT_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszAirportErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	airportCreate

 Description: Initializes the airport queues and the statistic values

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportCreate (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportCreate", ERROR_NO_AIRPORT_CREATE);
	}
	pqueueCreate (&psAirport->sLandingQueue);
	queueCreate (&psAirport->sTakeoffQueue);

	for (i = 0; NUMBER_OF_RUNWAYS > i; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}
	psAirport->availableRunway = 0;

	psAirport->sAirportStats.numCrashes =
			psAirport->sAirportStats.numEmergencyLandings =
					psAirport->sAirportStats.numLandingPlanes =
							psAirport->sAirportStats.numTakeoffPlanes =
									psAirport->sAirportStats.totalFlyingTimeRemaining =
											psAirport->sAirportStats.totalLandingTime =
													psAirport->sAirportStats.totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	airportTerminate

 Description: Terminates the airport queues and the statistic values

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportTerminate (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportTerminate", ERROR_NO_AIRPORT_TERMINATE);
	}
	pqueueTerminate (&psAirport->sLandingQueue);
	queueTerminate (&psAirport->sTakeoffQueue);

	for (i = 0; NUMBER_OF_RUNWAYS > i; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}
	psAirport->availableRunway = 0;

	psAirport->sAirportStats.numCrashes =
			psAirport->sAirportStats.numEmergencyLandings =
					psAirport->sAirportStats.numLandingPlanes =
							psAirport->sAirportStats.numTakeoffPlanes =
									psAirport->sAirportStats.totalFlyingTimeRemaining =
											psAirport->sAirportStats.totalLandingTime =
													psAirport->sAirportStats.totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	airportLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void airportLoadErrorMessages ()
{
	astatsLoadErrorMessages ();
	queueLoadErrorMessages ();
	LOAD_AIRPORT_ERRORS
}

/**************************************************************************
 Function: 	 	airportLandingQSize

 Description: Returns the size of the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	Size of the landing queue
 *************************************************************************/
int airportLandingQSize (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportLandingQSize", ERROR_INVALID_AIRPORT);
	}
	return pqueueSize (&psAirport->sLandingQueue);
}

/**************************************************************************
 Function: 	 	airportTakeoffQSize

 Description: Returns the size of the takeoff queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	Size of the takeoff queue
 *************************************************************************/
int airportTakeoffQSize (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportTakeoffQSize", ERROR_INVALID_AIRPORT);
	}
	return queueSize (&psAirport->sTakeoffQueue);
}

/**************************************************************************
 Function: 	 	airportQsAreEmpty

 Description: Checks if both queues are empty

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if both are empty; false otherwise
 *************************************************************************/
bool airportQsAreEmpty (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportQsAreEmpty", ERROR_INVALID_AIRPORT);
	}
	return 0 == pqueueSize (&psAirport->sLandingQueue) &&
			   0 == queueSize (&psAirport->sTakeoffQueue);
}

/**************************************************************************
 Function: 	 	airportAddLandingPlane

 Description: Adds a landing plane to the landing queue

 Parameters:	psAirport - pointer to the airport
   	 	 	 	 	 	time 	  	- current time in system (initial time plane added)
 	 	 	 	 	 	 	fuel 		  - fuel (time) remaining for plane

 Returned:	 	None
 *************************************************************************/
void airportAddLandingPlane (AirportPtr psAirport, const int time,
																									 const int fuel)
{
	if (NULL == psAirport)
	{
		processError ("airportAddLandingPlane", ERROR_INVALID_AIRPORT);
	}
	pqueueEnqueue (&psAirport->sLandingQueue, &time, sizeof (int), fuel);
	psAirport->sAirportStats.numLandingPlanes++;
}

/**************************************************************************
 Function: 	 	airportAddTakeoffPlane

 Description: Adds a takeoff plane to the takeoff queue

 Parameters:	psAirport - pointer to the airport
  	 	 	 	 	 	time 	  	- current time in system (initial time plane added)

 Returned:	 	None
 *************************************************************************/
void airportAddTakeoffPlane (AirportPtr psAirport, const int time)
{
	if (NULL == psAirport)
	{
		processError ("airportAddTakeoffPlane", ERROR_INVALID_AIRPORT);
	}
	queueEnqueue (&psAirport->sTakeoffQueue, &time, sizeof (int));
	psAirport->sAirportStats.numTakeoffPlanes++;
}

/**************************************************************************
 Function: 	 	airportLandPlane

 Description: Land a plane from the landing queue

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	 	clock 	  - current time in system

 Returned:	 	None
 *************************************************************************/
void airportLandPlane (AirportPtr psAirport, const int clock)
{
	int time, fuel;
	if (NULL == psAirport)
	{
		processError ("airportLandPlane", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		processError ("airportLandPlane", ERROR_EMPTY_AIRPORT);
	}
	pqueueDequeue (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);

	if (0 == fuel)
	{
		psAirport->sAirportStats.numEmergencyLandings++;
		psAirport->ezRunways[psAirport->availableRunway] = EMERGENCY;
	}
	else
	{
		psAirport->ezRunways[psAirport->availableRunway] = LANDING;
	}
	psAirport->sAirportStats.totalFlyingTimeRemaining += fuel;
	psAirport->sAirportStats.totalLandingTime += clock - time + 1;
	psAirport->availableRunway++;
}

/**************************************************************************
 Function: 	 	airportTakeoffPlane

 Description: Land a plane from the landing queue

 Parameters:	psAirport - pointer to the airport
  	 	 	 	 	 	clock 	  - current time in system


 Returned:	 	None
 *************************************************************************/
void airportTakeoffPlane (AirportPtr psAirport, const int clock)
{
	int time;
	if (NULL == psAirport)
	{
		processError ("airportTakeoffPlane", ERROR_INVALID_AIRPORT);
	}
	if (queueIsEmpty (&psAirport->sTakeoffQueue))
	{
		processError ("airportTakeoffPlane", ERROR_EMPTY_AIRPORT);
	}
	queueDequeue (&psAirport->sTakeoffQueue, &time, sizeof (int));
	psAirport->sAirportStats.totalTakeoffTime += clock - time + 1;
	psAirport->ezRunways[psAirport->availableRunway] = TAKEOFF;
	psAirport->availableRunway++;
}

/**************************************************************************
 Function: 	 	airportCrashPlane

 Description: Crash a plane from the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportCrashPlane (AirportPtr psAirport, const int clock)
{
	int time, fuel;
	if (NULL == psAirport)
	{
		processError ("airportCrashPlane", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		processError ("airportCrashPlane", ERROR_EMPTY_AIRPORT);
	}
	pqueueDequeue (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);
	psAirport->sAirportStats.numCrashes++;
	psAirport->sAirportStats.totalFlyingTimeRemaining += fuel;
	psAirport->sAirportStats.totalLandingTime += clock - time + 1;
}

/**************************************************************************
 Function: 	 	airportHandleEmergencies

 Description: Land or crash all emergency planes

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	 	clock 	  - current time in system

 Returned:	 	None
 *************************************************************************/
void airportHandleEmergencies (AirportPtr psAirport, const int clock)
{
	if (NULL == psAirport)
	{
		processError ("airportHandleEmergencies", ERROR_INVALID_AIRPORT);
	}
	while (airportHasEmergency (psAirport))
	{
		if (airportRunwayHasOpen (psAirport))
		{
			airportLandPlane (psAirport, clock);
		}
		else
		{
			airportCrashPlane (psAirport, clock);
		}
	}
}

/**************************************************************************
 Function: 	 	airportAssignRunways

 Description: Assign planes to the runways until runways full or queues empty

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	 	clock 	  - current time in system

 Returned:	 	None
 *************************************************************************/
void airportAssignRunways (AirportPtr psAirport, const int clock)
{
	if (NULL == psAirport)
	{
		processError ("airportAssignRunways", ERROR_INVALID_AIRPORT);
	}
	while (airportRunwayHasOpen (psAirport) && !airportQsAreEmpty (psAirport))
	{
		if (pqueueSize (&psAirport->sLandingQueue)
						>= queueSize (&psAirport->sTakeoffQueue))
		{
			airportLandPlane (psAirport, clock);
		}
		else
		{
			airportTakeoffPlane (psAirport, clock);
		}
	}
}

/**************************************************************************
 Function: 	 	airportResetRunways

 Description: Resets all runways to empty

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
extern void airportResetRunways (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportResetRunways", ERROR_INVALID_AIRPORT);
	}
	for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}
	psAirport->availableRunway = 0;
}

/**************************************************************************
 Function: 	 	airportDecrementFuel

 Description: Decrement fuel in landing planes

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportDecrementFuel (AirportPtr psAirport)
{
	const int DECREMENT = -1;
	if (NULL == psAirport)
	{
		processError ("airportDecrementFuel", ERROR_INVALID_AIRPORT);
	}
	pqueueChangePriority (&psAirport->sLandingQueue, DECREMENT);
}

/**************************************************************************
 Function: 	 	airportGetRunwayStatus

 Description: Increment/decrement all planes in queues appropriately

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	  number	  - number of the runway to return

 Returned:	 	An int representing the status of the runway
 *************************************************************************/
int airportGetRunwayStatus (const AirportPtr psAirport, const int number)
{
	if (NULL == psAirport)
	{
		processError ("airportGetRunwayStatus", ERROR_INVALID_AIRPORT);
	}
	return psAirport->ezRunways[number];
}

/**************************************************************************
 Function: 	 	airportHasEmergency

 Description: Checks if a landing plane needs an emergency landing

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if a landing plane has no fuel; false otherwise
 *************************************************************************/
bool airportHasEmergency (const AirportPtr psAirport)
{
	int time = 0, fuel = 0;
	if (NULL == psAirport)
	{
		processError ("airportHasEmergency", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		return false;
	}
	else
	{
		pqueuePeek (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);
		return 0 == fuel;
	}
}

/**************************************************************************
 Function: 	 	airportRunwayHasOpen

 Description: Checks if at least one runway is empty/open

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if a runway is open; false otherwise
 *************************************************************************/
bool airportRunwayHasOpen (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportRunwayHasOpen", ERROR_INVALID_AIRPORT);
	}
	return NUMBER_OF_RUNWAYS > psAirport->availableRunway;
}

/**************************************************************************
 Function: 	 	airportAverageLandingTime

 Description: Return the average landing waiting time

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average landing waiting time
 *************************************************************************/
float airportAverageLandingTime (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportAverageLandingTime", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalLandingTime
				 / psAirport->sAirportStats.numLandingPlanes;
}

/**************************************************************************
 Function: 	 	airportAverageTakeoffTime

 Description: Return the average takeoff waiting time

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average takeoff waiting time
 *************************************************************************/
float airportAverageTakeoffTime (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportAverageTakeoffTime", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalTakeoffTime
				 / psAirport->sAirportStats.numTakeoffPlanes;
}

/**************************************************************************
 Function: 	 	airportAverageFlyingTimeRemaining

 Description: Return the average flying time remaining

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average flying time remaining
 *************************************************************************/
float airportAverageFlyingTimeRemaining (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportAverageFlyingTimeRemaining", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalFlyingTimeRemaining
				 / psAirport->sAirportStats.numLandingPlanes;
}

/**************************************************************************
 Function: 	 	airportNumEmergencyLandings

 Description: Return the number of emergency landings

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The number of emergency landings
 *************************************************************************/
int airportNumEmergencyLandings (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportNumEmergencyLandings", ERROR_INVALID_AIRPORT);
	}
	return psAirport->sAirportStats.numEmergencyLandings;
}

/**************************************************************************
 Function: 	 	airportNumCrashes

 Description: Return the number of crashes

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The number of crashes
 *************************************************************************/
int airportNumCrashes (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportNumCrashes", ERROR_INVALID_AIRPORT);
	}
	return psAirport->sAirportStats.numCrashes;
}
