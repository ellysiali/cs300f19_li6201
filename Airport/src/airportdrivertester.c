/**************************************************************************
 File name:  airportdrivertester.c
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Testing of an Airport Simulator
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/airport.h"
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"

#define LONG_QUEUE_LENGTH 1000
#define VERY_LONG_QUEUE_LENGTH 1000000
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define GAS_VALUE 999
#define INCREMENTED 78
#define GAS_EMPTY 0
#define SINGLE 1

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
static void assert (bool bExpression, char *pTrue, char *pFalse)
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

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the airport system

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main ()
{
	Airport sTheAirport;
	int i, clock = 0, time, gas;

	puts ("Driver Start");

	airportLoadErrorMessages (&sTheAirport);

	// Validate for airportCreate

	airportCreate (&sTheAirport);
	assert (airportQsAreEmpty (&sTheAirport) &&
					0 == airportLandingQSize (&sTheAirport) &&
					0 == airportTakeoffQSize (&sTheAirport),
			"Initial landing and takeoff queues are empty",
			"Initial landing and takeoff queues are NOT empty");
	assert (airportQsAreEmpty (&sTheAirport) &&
				  EMPTY == airportGetRunwayStatus (&sTheAirport, FIRST) &&
			    EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND) &&
					EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
					"Initial runways are all empty",
					"Initial runways are NOT all empty");
	assert (0 == sTheAirport.sAirportStats.totalTakeoffTime &&
				  0 == sTheAirport.sAirportStats.totalLandingTime &&
					0 == sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
					0 == sTheAirport.sAirportStats.numTakeoffPlanes &&
					0 == sTheAirport.sAirportStats.numLandingPlanes &&
					0 == sTheAirport.sAirportStats.numEmergencyLandings &&
					0 == sTheAirport.sAirportStats.numCrashes,
					"Initial airport statistics are zero\n",
					"Initial airport statistics are NOT zero\n");

	// Add planes to both queues and ensure the sizes are correct

	for (i = 0; VERY_LONG_QUEUE_LENGTH > i; i++)
	{
		airportAddLandingPlane (&sTheAirport, clock, GAS_VALUE);
		airportAddTakeoffPlane (&sTheAirport, clock);

		if (i + 1 != airportLandingQSize (&sTheAirport))
		{
			assert (i + 1 == airportLandingQSize (&sTheAirport),
								"Landing queue size is correct",
								"Could not validate landing queue size is correct");
		}
		if (i + 1 != airportTakeoffQSize (&sTheAirport))
		{
			assert (i + 1 == airportTakeoffQSize (&sTheAirport),
								"Takeoff queue size is correct",
								"Could not validate takeoff queue size is correct");
		}
	}

	success ("Added planes correctly to both queues\n");

	// Validate airportTerminate works appropriately

	airportTerminate (&sTheAirport);
	assert (airportQsAreEmpty (&sTheAirport),
			"Terminated landing and takeoff queues are empty",
			"Terminated landing and takeoff queues are NOT empty");
	assert (EMPTY == airportGetRunwayStatus (&sTheAirport, FIRST) &&
			    EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND) &&
					EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
					"Terminated runways are all empty",
					"Terminated runways are NOT all empty");
	assert (0 == sTheAirport.sAirportStats.totalTakeoffTime &&
				  0 == sTheAirport.sAirportStats.totalLandingTime &&
					0 == sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
					0 == sTheAirport.sAirportStats.numTakeoffPlanes &&
					0 == sTheAirport.sAirportStats.numLandingPlanes &&
					0 == sTheAirport.sAirportStats.numEmergencyLandings &&
					0 == sTheAirport.sAirportStats.numCrashes,
					"Terminated airport statistics are zero\n",
					"Terminated airport statistics are NOT zero\n");

	// Validate airportDecrementFuel works correctly

	airportCreate (&sTheAirport);
	airportAddLandingPlane (&sTheAirport, clock, GAS_VALUE);
	for (i = 0; INCREMENTED > i; i++)
	{
		airportDecrementFuel (&sTheAirport);
	}
	pqueuePeek (&sTheAirport.sLandingQueue, &time, sizeof (int), &gas);
	assert (GAS_VALUE - INCREMENTED == gas,
			"Landing plane decremented correctly\n",
			"Landing plane NOT decremented correctly\n");
	airportTerminate (&sTheAirport);

	// Validate airportAssignRunways when only one landing plane

	airportCreate (&sTheAirport);
	airportAddLandingPlane (&sTheAirport, clock, GAS_VALUE);
	airportAssignRunways (&sTheAirport, clock);

	if (!airportQsAreEmpty (&sTheAirport))
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane landed correctly",
				"Single plane NOT landed correctly (size error)");
	}
	if (LANDING != airportGetRunwayStatus (&sTheAirport, FIRST))
	{
		assert (LANDING == airportGetRunwayStatus (&sTheAirport, FIRST),
				"Single plane landed correctly",
				"Single plane NOT landed correctly (runway 1 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, SECOND))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND),
				"Single plane landed correctly",
				"Single plane NOT landed correctly (runway 2 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, THIRD))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
				"Single plane landed correctly",
				"Single plane NOT landed correctly (runway 3 error)");
	}
	if (SINGLE != sTheAirport.sAirportStats.numLandingPlanes &&
			GAS_VALUE != sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
			0 != sTheAirport.sAirportStats.totalLandingTime)
	{
		assert (SINGLE == sTheAirport.sAirportStats.numLandingPlanes &&
				GAS_VALUE == sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
				0 == sTheAirport.sAirportStats.totalLandingTime,
				"Single plane landed correctly",
				"Single plane NOT landed correctly (statistic error)");
	}

	// Validate airportResetRunways

	airportResetRunways (&sTheAirport);
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, FIRST))
	{
		assert (LANDING == airportGetRunwayStatus (&sTheAirport, FIRST),
				"Runways reset correctly",
				"Runways NOT reset correctly (runway 1 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, SECOND))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND),
				"Runways reset correctly",
				"Runways NOT reset correctly (runway 2 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, THIRD))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
				"Runways reset correctly",
				"Runways NOT reset correctly (runway 3 error)");
	}

	// Validate airportAssignRunways when only one takeoff plane

	airportAddTakeoffPlane (&sTheAirport, clock);
	airportAssignRunways (&sTheAirport, clock);

	if (!airportQsAreEmpty (&sTheAirport))
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane took off correctly",
				"Single plane did NOT takeoff correctly (size error)");
	}
	if (TAKEOFF != airportGetRunwayStatus (&sTheAirport, FIRST))
	{
		assert (TAKEOFF == airportGetRunwayStatus (&sTheAirport, FIRST),
				"Single plane took off correctly",
				"Single plane did NOT takeoff correctly (runway 1 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, SECOND))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND),
				"Single plane took off correctly",
				"Single plane did NOT takeoff correctly (runway 2 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, THIRD))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
				"Single plane took off correctly",
				"Single plane did NOT takeoff correctly (runway 3 error)");
	}
	if (SINGLE != sTheAirport.sAirportStats.numTakeoffPlanes &&
			0 != sTheAirport.sAirportStats.totalTakeoffTime)
	{
		assert (SINGLE == sTheAirport.sAirportStats.numTakeoffPlanes &&
				0 == sTheAirport.sAirportStats.totalTakeoffTime,
				"Single plane took off correctly",
				"Single plane did NOT takeoff correctly (statistic error)");
	}

	airportTerminate (&sTheAirport);

	// Validate airportAssignRunways when one plane of each

	airportCreate (&sTheAirport);

	airportResetRunways (&sTheAirport);
	airportAddLandingPlane (&sTheAirport, clock, GAS_VALUE);
	airportAddTakeoffPlane (&sTheAirport, clock);
	airportAssignRunways (&sTheAirport, clock);

	if (!airportQsAreEmpty (&sTheAirport))
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Planes assigned correctly",
				"Planes NOT assigned correctly (size error)");
	}
	if (LANDING != airportGetRunwayStatus (&sTheAirport, FIRST))
	{
		assert (LANDING == airportGetRunwayStatus (&sTheAirport, FIRST),
				"Planes assigned correctly",
				"Planes NOT assigned correctly (runway 1 error)");
	}
	if (TAKEOFF != airportGetRunwayStatus (&sTheAirport, SECOND))
	{
		assert (TAKEOFF == airportGetRunwayStatus (&sTheAirport, SECOND),
				"Planes assigned correctly",
				"Planes NOT assigned correctly (runway 2 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, THIRD))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
				"Planes assigned correctly",
				"Planes NOT assigned correctly (runway 3 error)");
	}
	if (SINGLE != sTheAirport.sAirportStats.numLandingPlanes &&
			SINGLE != sTheAirport.sAirportStats.numTakeoffPlanes &&
			GAS_VALUE != sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
			0 != sTheAirport.sAirportStats.totalLandingTime &&
			0 != sTheAirport.sAirportStats.totalTakeoffTime)
	{
		assert (SINGLE == sTheAirport.sAirportStats.numLandingPlanes &&
				SINGLE == sTheAirport.sAirportStats.numTakeoffPlanes &&
				GAS_VALUE == sTheAirport.sAirportStats.totalFlyingTimeRemaining &&
				SINGLE == sTheAirport.sAirportStats.totalLandingTime &&
				SINGLE == sTheAirport.sAirportStats.totalTakeoffTime,
				"Planes assigned correctly",
				"Planes NOT assigned correctly (statistic error)");
	}

	airportTerminate (&sTheAirport);

	// Validate airportHandleEmergencies for an emergency landing

	airportCreate (&sTheAirport);

	airportResetRunways (&sTheAirport);
	airportAddLandingPlane (&sTheAirport, clock, GAS_EMPTY);
	airportHandleEmergencies (&sTheAirport, clock);

	if (!airportQsAreEmpty (&sTheAirport))
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane emergency landed correctly",
				"Single plane emergency NOT landed correctly (size error)");
	}
	if (EMERGENCY != airportGetRunwayStatus (&sTheAirport, FIRST))
	{
		assert (EMERGENCY == airportGetRunwayStatus (&sTheAirport, FIRST),
				"Single plane emergency landed correctly",
				"Single plane emergency NOT landed correctly (runway 1 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, SECOND))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, SECOND),
				"Single plane emergency landed correctly",
				"Single plane emergency NOT landed correctly (runway 2 error)");
	}
	if (EMPTY != airportGetRunwayStatus (&sTheAirport, THIRD))
	{
		assert (EMPTY == airportGetRunwayStatus (&sTheAirport, THIRD),
				"Single plane emergency landed correctly",
				"Single plane emergency NOT landed correctly (runway 3 error)");
	}
	if (SINGLE != sTheAirport.sAirportStats.numEmergencyLandings)
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane emergency landed correctly",
				"Single plane emergency NOT landed correctly (statistic error)");
	}

	// Validate airportHandleEmergencies for a crashed plane

	airportResetRunways (&sTheAirport);
	for (i = 0; NUMBER_OF_RUNWAYS + 1 > i; i++)
	{
		airportAddLandingPlane (&sTheAirport, clock, GAS_EMPTY);
	}
	airportHandleEmergencies (&sTheAirport, clock);
	if (!airportQsAreEmpty (&sTheAirport))
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane crashed correctly",
				"Single plane NOT crashed correctly (size error)");
	}
	if (SINGLE != sTheAirport.sAirportStats.numCrashes)
	{
		assert (airportQsAreEmpty (&sTheAirport),
				"Single plane crashed correctly",
				"Single plane NOT crashed correctly (statistic error)");
	}

	success ("Validated minimal test cases for removing airplanes from queues\n");

	airportTerminate (&sTheAirport);

	puts ("Driver End");

	return EXIT_SUCCESS;
}
