/**************************************************************************
 File name:  airportdriver.c
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Running of an Airport Simulator
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/airport.h"
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

//int main ()
int main (int argc, char* argv[])
{
	const char STATUS_CHARS[] = {'-', 'T', 'L', 'E'};
	Airport sTheAirport;
	int i, clock = 0, numLandingPlanes, numTakeoffPlanes,
	    landingFuels[NUMBER_OF_RUNWAYS], numCrashes;
	FILE* pInFile = NULL;

	airportLoadErrorMessages (&sTheAirport);
	airportCreate (&sTheAirport);

  // Check number of arguments
  if( argc != 2 )
  {
    printf("Invalid number of arguments\n");
    return EXIT_FAILURE;
  }


//	pInFile = fopen("data/airport.txt", "r");
  pInFile = fopen(argv[1], "r");

  if (NULL == pInFile) {
     printf("Could not open file\n");
     return EXIT_FAILURE;
  }

  while (!feof(pInFile) || !airportQsAreEmpty (&sTheAirport))
  {
  	numCrashes = numTakeoffPlanes = numLandingPlanes = 0;
  	airportResetRunways (&sTheAirport);
  	if (!feof(pInFile))
		{
			fscanf (pInFile, "%d %d %d %d %d", &numTakeoffPlanes, &numLandingPlanes,
					&landingFuels[FIRST], &landingFuels[SECOND], &landingFuels[THIRD]);
			for (i = 0; i < numTakeoffPlanes; i++)
			{
				airportAddTakeoffPlane (&sTheAirport);
			}
			for (i = 0; i < numLandingPlanes; i++)
			{
				airportAddLandingPlane (&sTheAirport, landingFuels[i]);
			}
		}
  	airportDecrementFuel (&sTheAirport);
  	airportAssignRunways (&sTheAirport);

  	while (airportHasEmergency (&sTheAirport))
  	{
  		airportCrashPlane (&sTheAirport);
  		numCrashes++;
  	}

  	// print results
  	if (0 == clock % REPRINT_HEADER)
  	{
  		printf ("%6c%23s%13c%13s%7c%8s%9s\n", '|', "Planes Added", '|', "Runways",
  																				'|', "Queue", "Lengths");
  		printf ("%6s%8s%28s%20s%17s\n", "Time |", "Takeoff",
  														   "Landing (Fuel Remaining) |",
																 "1   2   3  Crash |", "Takeoff  Landing");
  		puts ("---- | -------  ------------------------ | --- --- --- ----- | "
  				"-------  -------");
  	}
		printf ("%4d |%8d%9d |", clock, numTakeoffPlanes, numLandingPlanes);
		for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
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
		for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
		{
			printf ("%3c ", STATUS_CHARS[airportGetRunwayStatus (&sTheAirport, i)]);
		}
		printf ("%6d |%8d", numCrashes, airportTakeoffQSize (&sTheAirport));
		printf ("%9d\n", airportLandingQSize (&sTheAirport));


  	clock++;
  }

  // print statistics; use %g or %d

  printf ("\nAverage takeoff waiting time: %g\n",
  				getAverageTakeoffTime (&sTheAirport));
  printf ("Average landing waiting time: %g\n",
  				getAverageLandingTime (&sTheAirport));
  printf ("Average flying time remaining on landing: %g\n",
  				getAverageFlyingTimeRemaining (&sTheAirport));
  printf ("Number of planes landing with zero fuel: %d\n",
  				 getNumEmergencyLandings (&sTheAirport));
  printf ("Number of crashes: %d\n", getNumCrashes (&sTheAirport));


	airportTerminate (&sTheAirport);

  fclose(pInFile);

	return EXIT_SUCCESS;
}
