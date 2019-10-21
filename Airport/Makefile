######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 20, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the Airport Simulator
######################################################################

.PHONY: all clean

all: bin/airportdriver bin/airportdrivertester

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o
	gcc -o bin/airportdriver bin/airportdriver.o bin/airport.o -g -Wall
	
bin/airportdriver.o: src/airportdriver.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	gcc -c -o bin/airportdriver.o src/airportdriver.c -g -Wall
	
bin/airportdrivertester: bin/airportdrivertester.o bin/airport.o \
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o
	gcc -o bin/airportdrivertester bin/airportdrivertester.o \
	bin/airport.o -g -Wall
	
bin/airportdrivertester.o: src/airportdrivertester.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	gcc -c -o bin/airportdrivertester.o src/airportdrivertester.c -g -Wall

bin/airport.o: src/airport.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	gcc -c -o bin/airport.o src/airport.c -g -Wall
	
../GenericDynamicQ/bin/queue.o:
	cd ../GenericDynamicQ; make bin/queue.o	
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o

tarball: clean
	tar czf ../cs300_4_li6201.tar.gz ../GenericDynamicList \
../GenericDynamicPriorityQ ../GenericDynamicPriorityQ ../Airport

clean:
	cd ../GenericDynamicList; make clean
	rm -rf bin/*.o bin/GenericDynamicPriorityQ
	
valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/airportdriver data/airport.txt