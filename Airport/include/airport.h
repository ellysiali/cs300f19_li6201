/**************************************************************************
 File name:  airport.h
 Author:     Ellysia Li
 Date:		   Oct 31, 2019
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    This file defines the constants, data structures, and
             function prototypes for implementing an airport simulator
 *************************************************************************/
#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <stdbool.h>
#include "../include/airportstats.h"
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_AIRPORT_CHARS 64
#define NUMBER_OF_RUNWAYS 3

enum {NO_AIRPORT_ERROR = 0,
			ERROR_NO_AIRPORT_CREATE,
			ERROR_NO_AIRPORT_TERMINATE,
			ERROR_INVALID_AIRPORT,
			ERROR_INVALID_RUNWAY,
			ERROR_NULL_AIRPORT_PTR,
			ERROR_EMPTY_AIRPORT};

#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_AIRPORT - NO_AIRPORT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy (gszAirportErrors[NO_AIRPORT_ERROR], \
		"No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE], \
		"Error: No Airport Create.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_TERMINATE], \
		"Error: No Airport Terminate.");\
strcpy(gszAirportErrors[ERROR_INVALID_AIRPORT], "Error: Invalid Airport.");\
strcpy(gszAirportErrors[ERROR_INVALID_RUNWAY], "Error: Full Runway.");\
strcpy(gszAirportErrors[ERROR_NULL_AIRPORT_PTR], "Error: NULL Pointer.");\
strcpy(gszAirportErrors[ERROR_EMPTY_AIRPORT], "Error: Empty Airport.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef enum Runway {EMPTY = 0, TAKEOFF, LANDING, EMERGENCY} Runway;

typedef struct Airport
{
	Runway ezRunways [NUMBER_OF_RUNWAYS];
	int availableRunway, clock;
	PriorityQueue sLandingQueue;
	Queue sTakeoffQueue;
	AirportStats sAirportStats;
} Airport;

typedef Airport* AirportPtr;

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void airportCreate (AirportPtr psAirport);
// results: If airport can be created, then airport exists and is empty
//					otherwise, ERROR_NO_AIRPORT_CREATE

extern void airportTerminate (AirportPtr psAirport);
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_AIRPORT_TERMINATE

extern void airportLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*							Checking number of elements in Airport's queues
**************************************************************************/
extern int airportLandingQSize (const AirportPtr psAirport);
// results: Returns the number of elements in the LandingQ
// 					error code priority: ERROR_INVALID_AIRPORT if AIRPORT is NULL

extern int airportTakeoffQSize (const AirportPtr psAirport);
// results: Returns the number of elements in the TakeoffQ
// 					error code priority: ERROR_INVALID_AIRPORT if AIRPORT is NULL

extern bool airportQsAreEmpty (const AirportPtr psAirport);
// results: If both Q's are empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_AIRPORT

/**************************************************************************
*										Inserting, Deleting, and Updating
**************************************************************************/
extern void airportAddLandingPlane (AirportPtr psAirport, const int fuel);
// results: Insert a plane to the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportAddTakeoffPlane (AirportPtr psAirport);
// results: Insert a plane to the takeoff queue.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportHandleEmergencies (AirportPtr psAirport);
// results: Lands or crashes all emergency planes from the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportAssignRunways (AirportPtr psAirport);
// results: Assign the appropriate planes to runways (if necessary) and update
//          the queues appropriately
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportUpdateRunwayStatus (AirportPtr psAirport, int status);
// requires: ezRunways has an empty runway
// results: Updates the first empty runway to the appropriate status
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportResetRunways (AirportPtr psAirport);
// results: Resets runways to empty
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportDecrementFuel (AirportPtr psAirport);
// results: decrement the fuel of each plane by one.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportIncrementClock (AirportPtr psAirport);
// results: increment the clock by one.
//					error code priority: ERROR_INVALID_AIRPORT

/**************************************************************************
*														Get Operations
**************************************************************************/
extern int airportGetClock (const AirportPtr psAirport);
// results: Returns the time on the clock
// 					error code priority: ERROR_INVALID_AIRPORT

extern int airportGetRunwayStatus (const AirportPtr psAirport,
																		const int number);
// results: Returns the status of the (number)th runway
// 					error code priority: ERROR_INVALID_AIRPORT

extern double airportAverageLandingTime (const AirportPtr psAirport);
// results: Return the average landing waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

extern double airportAverageTakeoffTime (const AirportPtr psAirport);
// results: Return the average takeoff waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

extern double airportAverageFlyingTimeRemaining (const AirportPtr psAirport);
// results: Return the average flying time remaining
// 					error code priority: ERROR_INVALID_AIRPORT

extern int airportNumEmergencyLandings (const AirportPtr psAirport);
// results: Return the number of emergency landings
// 					error code priority: ERROR_INVALID_AIRPORT

extern int airportNumCrashes (const AirportPtr psAirport);
// results: Return the number of crashes
// 					error code priority: ERROR_INVALID_AIRPORT

#endif /* AIRPORT_H_ */

