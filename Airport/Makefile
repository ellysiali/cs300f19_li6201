######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 30, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the Airport Simulator
######################################################################

.PHONY: all clean

all: bin/airportdriver bin/airportdrivertester test1

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
	gcc -o bin/airportdriver bin/airportdriver.o bin/airport.o \
	../GenericDynamicQ/bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o -g -Wall
	
bin/airportdriver.o: src/airportdriver.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airportdriver.o src/airportdriver.c -g -Wall
	
bin/airportdrivertester: bin/airportdrivertester.o bin/airport.o \
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/airportdrivertester bin/airportdrivertester.o \
	bin/airport.o ../GenericDynamicQ/bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/airportdrivertester.o: src/airportdrivertester.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airportdrivertester.o src/airportdrivertester.c -g -Wall

bin/airport.o: src/airport.c include/airport.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airport.o src/airport.c -g -Wall
	
../GenericDynamicQ/bin/queue.o: \
../GenericDynamicQ/src/queue.c ../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	cd ../GenericDynamicQ; make bin/queue.o	
	
../GenericDynamicPriorityQ/bin/pqueue.o: \
../GenericDynamicPriorityQ/src/pqueue.c \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o
	
test1: bin/airportdriver
	bin/airportdriver data/airport1.txt > bin/airport1_actual.txt
	diff -s data/airport1_expected.txt bin/airport1_actual.txt
	
tarball: clean
	tar czf ../cs300_4_li6201.tar.gz ../GenericDynamicList \
	../GenericDynamicPriorityQ ../GenericDynamicPriorityQ ../Airport

clean:
	cd ../GenericDynamicQ; make clean
	rm -rf bin/*.o bin/Airport
	
valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/airportdriver data/airport.txt