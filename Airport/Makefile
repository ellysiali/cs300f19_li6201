######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 31, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the Airport Simulator
######################################################################

.PHONY: all clean

all: bin/airportdriver bin/airportdrivertester

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o bin/airportstats.o \
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/airportdriver bin/airportdriver.o bin/airport.o \
	bin/airportstats.o \
	../GenericDynamicQ/bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/airportdriver.o: src/airportdriver.c include/airport.h \
include/airportstats.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airportdriver.o src/airportdriver.c -g -Wall
	
bin/airportdrivertester: bin/airportdrivertester.o bin/airport.o \
bin/airportstats.o\
../GenericDynamicQ/bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/airportdrivertester bin/airportdrivertester.o \
	bin/airport.o bin/airportstats.o ../GenericDynamicQ/bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/airportdrivertester.o: src/airportdrivertester.c include/airport.h \
include/airportstats.h\
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airportdrivertester.o src/airportdrivertester.c -g -Wall

bin/airport.o: src/airport.c include/airport.h include/airportstats.h \
../GenericDynamicQ/include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/airport.o src/airport.c -g -Wall
	
bin/airportstats.o: src/airportstats.c include/airportstats.h
	gcc -c -o bin/airportstats.o src/airportstats.c -g -Wall
	
../GenericDynamicQ/bin/queue.o:
	cd ../GenericDynamicQ; make bin/queue.o	
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

test1: bin/airportdriver
	bin/airportdriver data/airport1.txt > bin/airport1_actual.txt
	diff -s data/airport1_expected.txt bin/airport1_actual.txt
	
test2: bin/airportdriver
	bin/airportdriver data/airport.txt
	
tarball: clean
	tar czf ../cs300_4_li6201.tar.gz ../GenericDynamicList \
	../GenericDynamicPriorityQ ../GenericDynamicQ ../Airport

clean:
	cd ../GenericDynamicQ; make clean
	rm -rf bin/*.o bin/Airport
	
valgrind: bin/airportdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/airportdriver data/airport.txt