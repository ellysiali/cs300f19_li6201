/**************************************************************************
 File name:  airport.h
 Author:     Ellysia Li
 Date:		   Oct 20, 2019
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    This file defines the constants, data structures, and
             function prototypes for implementing an airport simulator
 *************************************************************************/

#include <stdbool.h>
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
			ERROR_FULL_RUNWAY,
			ERROR_NULL_AIRPORT_PTR,
			ERROR_EMPTY_AIRPORT};

#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_AIRPORT - NO_AIRPORT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy(gszAirportErrors[NO_AIRPORT_ERROR], \
		"No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE], \
		"Error: No Airport Create.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_TERMINATE], \
		"Error: No Airport Terminate.");\
strcpy(gszAirportErrors[ERROR_INVALID_AIRPORT], "Error: Invalid Airport.");\
strcpy(gszAirportErrors[ERROR_FULL_RUNWAY], "Error: Full Runway.");\
strcpy(gszAirportErrors[ERROR_NULL_AIRPORT_PTR], "Error: NULL Pointer.");\
strcpy(gszAirportErrors[ERROR_EMPTY_AIRPORT], "Error: Empty Airport.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef enum Runway {EMPTY = 0, TAKEOFF, LANDING, EMERGENCY} Runway;

typedef struct AirportStats
{
		int totalTakeoffTime, totalLandingTime, totalFlyingTimeRemaining,
		    numTakeoffs, numLandings, numEmergencyLandings, numCrashes;
} AirportStats;

typedef struct Airport
{
	int clock;
	Runway ezRunways [NUMBER_OF_RUNWAYS];
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
extern void airportAddLandingPlane (AirportPtr psAirport, const int time,
																												  const int gas);
// results: Insert a plane to the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportAddTakeoffPlane (AirportPtr psAirport, const int time);
// results: Insert a plane to the takeoff queue.
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportLandPlane (AirportPtr psAirport);
// results: Remove a plane from the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

extern void airportTakeoffPlane (AirportPtr psAirport);
// results: Remove a plane from the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

extern void airportCrashPlane (AirportPtr psAirport);
// results: Crash planes from the landing queue.
//					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

extern void airportAssignRunways (AirportPtr psAirport);
// results: Assign the appropriate planes to runways (if necessary) and update
//          the queues appropriately
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportUpdateRunwayStatus (AirportPtr psAirport, int status);
// requires: ezRunways has an empty runway
// results: Updates the first empty runway to the appropriate status
//					error code priority: ERROR_INVALID_AIRPORT

extern void airportIncrementClock (AirportPtr psAirport);
// results: Increment/decrement the time/gas of each airplane by one.
//					error code priority: ERROR_INVALID_AIRPORT

/**************************************************************************
*													Get/Check/Peek Operations
**************************************************************************/
extern int airportGetRunwayStatus (const AirportPtr psAirport,
																		const int number);
// results: Returns the status of the (number)th runway
// 					error code priority: ERROR_INVALID_AIRPORT

extern bool airportHasEmergency (const AirportPtr psAirport);
// requires: psQueue is not empty
// results: If the landing queue has a priority of 0, return true; otherwise,
//          return false
// 					error code priority: ERROR_INVALID_AIRPORT, ERROR_EMPTY_AIRPORT

extern bool airportRunwayHasOpen (const AirportPtr psAirport);
// results: If at least one runway is empty, return true; otherwise, return
//          false
// 					error code priority: ERROR_INVALID_AIRPORT

extern bool airportRunwaysAreOpen (const AirportPtr psAirport);
// results: If at least one runway is empty, return true; otherwise, return
//          false
// 					error code priority: ERROR_INVALID_AIRPORT

extern float getAverageLandingTime (const AirportPtr psAirport);
// results: Return the average landing waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

extern float getAverageTakeoffTime (const AirportPtr psAirport);
// results: Return the average takeoff waiting time
// 					error code priority: ERROR_INVALID_AIRPORT

extern float getAverageFlyingTimeRemaining (const AirportPtr psAirport);
// results: Return the average flying time remaining
// 					error code priority: ERROR_INVALID_AIRPORT

extern int getNumEmergencyLandings (const AirportPtr psAirport);
// results: Return the number of emergency landings
// 					error code priority: ERROR_INVALID_AIRPORT

extern int getNumCrashes (const AirportPtr psAirport);
// results: Return the number of crashes
// 					error code priority: ERROR_INVALID_AIRPORT
