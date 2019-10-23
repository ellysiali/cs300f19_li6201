/**************************************************************************
 File name:  airportdrivertester.c
 Author:     Ellysia Li
 Date:		   Oct 20, 2019
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

int main ()
{
	List sTheList;
	PriorityQueue sThePQueue;
	Queue sTheQueue;

	puts ("Driver Start");

	lstCreate (&sTheList);
	pqueueCreate (&sThePQueue);
	queueCreate (&sTheQueue);

	puts ("Driver End");
	return EXIT_SUCCESS;
}
