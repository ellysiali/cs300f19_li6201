/**************************************************************************
 File name:  airport.c
 Author:     Ellysia Li
 Date:		   Oct 20, 2019
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

void airportCreate (AirportPtr psAirport)
{

}
// results: If airport can be created, then airport exists and is empty
//					otherwise, ERROR_NO_AIRPORT_CREATE


void airportTerminate (AirportPtr psAirport)
{

}
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_AIRPORT_TERMINATE

void airportLoadErrorMessages ()
{

}
// results:	Loads the error message strings for the error handler to use
//					No error conditions

int airportLandQSize (const AirportPtr psAirport)
{
	return 0;
}
// results: Returns the number of elements in the LandQ
// 					error code priority: ERROR_INVALID_AIRPORT if AIRPORT is NULL

int airportTakeoffQSize (const AirportPtr psAirport)
{
	return 0;
}
// results: Returns the number of elements in the TakeoffQ
// 					error code priority: ERROR_INVALID_AIRPORT if AIRPORT is NULL

bool airportQsAreEmpty (const AirportPtr psAirport)
{
	return true;
}
// results: If both Q's are empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_AIRPORT

void airportAddLandPlane (AirportPtr psAirport, const int *pGas)
{

}
// results: Insert a plane to the land queue.
//					error code priority: ERROR_INVALID_AIRPORT, ERROR_NULL_AIRPORT_PTR

void airportAddTakeoffPlane (AirportPtr psAirport)
{

}
// results: Insert a plane to the takeoff queue.
//					error code priority: ERROR_INVALID_AIRPORT

void airportLandPlane (AirportPtr psAirport, int *pTime, int *pGas)
{

}
// results: Remove a plane from the land queue.
//					error code priority: ERROR_INVALID_AIRPORT,
//															 ERROR_NULL_AIRPORT_PTR, ERROR_EMPTY_AIRPORT

void airportTakeoffPlane (AirportPtr psAirport, int *pTime)
{

}
// results: Remove a plane from the land queue.
//					error code priority: ERROR_INVALID_AIRPORT,
//															 ERROR_NULL_AIRPORT_PTR, ERROR_EMPTY_AIRPORT

void airportCrashPlane (AirportPtr psAirport, int *pTime)
{

}
// results: Crash a plane from the land queue.
//					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

void airportAssignRunways (AirportPtr psAirport)
{

}
// results: Assign the appropriate planes to runways (if necessary)
//					error code priority: ERROR_INVALID_AIRPORT

void airportIncrementClock (AirportPtr psAirport)
{

}
// results: Increment/decrement the time/gas of each airplane by one.
//					error code priority: ERROR_INVALID_AIRPORT

char airportGetRunwayStatus (const AirportPtr psAirport, const int number)
{
	return true;
}
// results: Returns the status of the (number)th runway
// 					error code priority: ERROR_INVALID_AIRPORT

bool airportHasEmergency (const AirportPtr psAirport)
{
	return true;
}
// requires: psQueue is not empty
// results: If the land queue has a priority of 0, return true; otherwise,
//          return false
// 					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

bool airportRunwaysAreOpen (const AirportPtr psAirport)
{
	return true;
}
// results: If at least one runway is empty, return true; otherwise, return
//          false
// 					error code priority: ERROR_INVALID_AIRPORT

float getAverageLandingTime (const AirportPtr psAirport)
{
	return 0;
}
// results: Return the average landing waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

float getAverageTakeoffTime (const AirportPtr psAirport)
{
	return 0;
}
// results: Return the average takeoff waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

float getAverageFlyingTimeRemaining (const AirportPtr psAirport)
{
	return 0;
}
// results: Return the average flying time remaining
// 					error code priority: ERROR_INVALID_AIRPORT

float getNumEmergencyLandings (const AirportPtr psAirport)
{
	return 0;
}
// results: Return the number of emergency landings
// 					error code priority: ERROR_INVALID_AIRPORT

float getNumCrashes (const AirportPtr psAirport)
{
	return 0;
}
// results: Return the number of crashes
// 					error code priority: ERROR_INVALID_AIRPORT
