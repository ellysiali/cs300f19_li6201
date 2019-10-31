/**************************************************************************
 File name:  airportdriver.c
 Author:     Ellysia Li
 Date:		   Oct 31, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Running of an Airport Simulator
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/airport.h"
#include "../include/airportstats.h"
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"

#define FIRST 0
#define SECOND 1
#define THIRD 2
#define REPRINT_HEADER 20

/**************************************************************************
 Function: 	 	main

 Description: Implement the Airport Simulation using the Airport structure

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/

int main (int argc, char* argv[])
{
	const char STATUS_CHARS[] = {'-', 'T', 'L', 'E'};
	int i, numLandingPlanes, numTakeoffPlanes, oldNumCrashes,
		  landingFuels[NUMBER_OF_RUNWAYS];
	Airport sTheAirport;
	FILE* pInFile = NULL;

	airportLoadErrorMessages (&sTheAirport);
	airportCreate (&sTheAirport);

  // Check number of arguments

  if( argc != 2 )
  {
    printf("Invalid number of arguments\n");
    return EXIT_FAILURE;
  }

  // Check valid file

  pInFile = fopen(argv[1], "r");

  if (NULL == pInFile) {
     printf("Could not open file\n");
     return EXIT_FAILURE;
  }

  // Airport Simulation:

  while (!feof(pInFile) || !airportQsAreEmpty (&sTheAirport))
  {
  	// Reset values

  	numTakeoffPlanes = numLandingPlanes = 0;
  	oldNumCrashes = airportNumCrashes (&sTheAirport);
  	for (i = 0; NUMBER_OF_RUNWAYS > i; i++)
  	{
  		landingFuels[i] = 0;
  	}
  	airportResetRunways (&sTheAirport);

  	// Read line of data & add new planes

  	if (!feof(pInFile))
		{
			fscanf (pInFile, "%d %d %d %d %d", &numTakeoffPlanes, &numLandingPlanes,
					&landingFuels[FIRST], &landingFuels[SECOND], &landingFuels[THIRD]);
			for (i = 0; numTakeoffPlanes > i; i++)
			{
				airportAddTakeoffPlane (&sTheAirport);
			}
			for (i = 0; numLandingPlanes > i; i++)
			{
				airportAddLandingPlane (&sTheAirport, landingFuels[i]);
			}
		}

  	// Decrement fuel

  	airportDecrementFuel (&sTheAirport);

  	// Handle emergencies (land and then crash zero-fuel planes)

  	airportHandleEmergencies (&sTheAirport);

  	// Assign remaining runways

  	airportAssignRunways (&sTheAirport);

  	// Print Results

  	if (1 == airportGetClock (&sTheAirport) % REPRINT_HEADER)
  	{
  		puts ("     |           Planes Added            |      Runways      "
  					"|   Queue  Lengths");
  		puts ("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash "
  					"| Takeoff  Landing");
  		puts ("---- | -------  ------------------------ | --- --- --- ----- "
  					"| -------  -------");
  	}
		printf ("%4d |%8d%9d |", airportGetClock (&sTheAirport), numTakeoffPlanes,
														 numLandingPlanes);
		for (i = 0; NUMBER_OF_RUNWAYS > i; i++)
		{
			if (0 == landingFuels[i])
			{
				printf ("%5c", '-');
			}
			else
			{
				printf ("%5d", landingFuels[i]);
			}
		}
		printf (" |");
		for (i = 0; NUMBER_OF_RUNWAYS > i; i++)
		{
			printf ("%3c ", STATUS_CHARS[airportGetRunwayStatus (&sTheAirport, i)]);
		}
		printf ("%6d |%8d%9d\n", airportNumCrashes (&sTheAirport) - oldNumCrashes,
														 airportTakeoffQSize (&sTheAirport),
														 airportLandingQSize (&sTheAirport));

		// Increment clock

		airportIncrementClock (&sTheAirport);
  }

  // Print Statistics

  printf ("\nAverage takeoff waiting time: %g\n",
  				airportAverageTakeoffTime (&sTheAirport));
  printf ("Average landing waiting time: %g\n",
  				airportAverageLandingTime (&sTheAirport));
  printf ("Average flying time remaining on landing: %g\n",
  				airportAverageFlyingTimeRemaining (&sTheAirport));
  printf ("Number of planes landing with zero fuel: %d\n",
  				 airportNumEmergencyLandings (&sTheAirport));
  printf ("Number of crashes: %d", airportNumCrashes (&sTheAirport));

	airportTerminate (&sTheAirport);

  fclose (pInFile);

	return EXIT_SUCCESS;
}
