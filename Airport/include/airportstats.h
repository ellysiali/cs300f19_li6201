/**************************************************************************
 File name:  airportstats.h
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    This file defines the constants, data structures, and
             function prototypes for the airport stats structure
 *************************************************************************/

#ifndef AIRPORTSTATS_H_
#define AIRPORTSTATS_H_
#include <string.h>

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_ASTATS_CHARS 64

enum {NO_ASTATS_ERROR = 0,
			ERROR_NO_ASTATS_CREATE,
			ERROR_NO_ASTATS_TERMINATE,
			ERROR_INVALID_ASTATS};

#define NUMBER_OF_ASTATS_ERRORS ERROR_INVALID_ASTATS - NO_ASTATS_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_ASTATS_ERRORS strcpy (gszAStatsErrors[NO_ASTATS_ERROR], \
		"No Error.");\
strcpy(gszAStatsErrors[ERROR_NO_ASTATS_CREATE], \
		"Error: No Airport Create.");\
strcpy(gszAStatsErrors[ERROR_NO_ASTATS_TERMINATE], \
		"Error: No Airport Terminate.");\
strcpy(gszAStatsErrors[ERROR_INVALID_ASTATS], "Error: Invalid Airport.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct AirportStats
{
		int totalTakeoffTime, totalLandingTime, totalFlyingTimeRemaining,
		    numTakeoffPlanes, numLandingPlanes, numEmergencyLandings, numCrashes;
} AirportStats;

typedef AirportStats* AirportStatsPtr;

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void astatsLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//					No error conditions

extern void astatsCreate (AirportStatsPtr psAStats);
// results: If airport can be created, then airport exists and is empty
//					otherwise, ERROR_NO_ASTATS_CREATE

extern void astatsTerminate (AirportStatsPtr psAStats);
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_ASTATS_TERMINATE

/**************************************************************************
*										Inserting, Deleting, and Updating
**************************************************************************/
extern void astatsIncrementNumLandings (AirportStatsPtr psAStats);
// results: Increments number of landings by one

extern void astatsIncrementNumTakeoffs (AirportStatsPtr psAStats);
// results: Increments number of takeoffs by one

extern void astatsIncrementEmergencies (AirportStatsPtr psAStats);
// results: Increments number of emergency landings by one

extern void astatsIncrementCrashes (AirportStatsPtr psAStats);
// results: Increments number of crashes by one

extern void astatsAddTakeoffTime (AirportStatsPtr psAStats, const int time);
// results: Add to the total takeoff time

extern void astatsAddLandingTime (AirportStatsPtr psAStats, const int time);
// results: Add to the total landing time

extern void astatsAddFlyingTimeRemaining (AirportStatsPtr psAStats,
																					const int time);
// results: Add to the total flying time remaining

/**************************************************************************
*															Statistics
**************************************************************************/
extern double astatsAverageLandingTime (const AirportStatsPtr psAStats);
// results: Return the average landing waiting time
// 					error code priority: ERROR_NO_ASTATS_CREATE

extern double astatsAverageTakeoffTime (const AirportStatsPtr psAStats);
// results: Return the average takeoff waiting time
// 					error code priority: ERROR_INVALID_ASTATS

extern double astatsAverageFlyingTimeRemaining (const AirportStatsPtr psAStats);
// results: Return the average flying time remaining
// 					error code priority: ERROR_INVALID_ASTATS

extern int astatsNumEmergencyLandings (const AirportStatsPtr psAStats);
// results: Return the number of emergency landings
// 					error code priority: ERROR_INVALID_ASTATS

extern int astatsNumCrashes (const AirportStatsPtr psAStats);
// results: Return the number of crashes
// 					error code priority: ERROR_INVALID_ASTATS

#endif /* AIRPORTSTATS_H_ */
