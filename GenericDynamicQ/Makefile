######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 20, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the General Queue
######################################################################

.PHONY: all clean

all: bin/queuedriver 

bin: 
	mkdir -p bin

bin/queuedriver: bin/queuedriver.o bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o
	gcc -o bin/queuedriver bin/queuedriver.o bin/queue.o -g -Wall
	
bin/queuedriver.o: src/queuedriver.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	gcc -c -o bin/queuedriver.o src/queuedriver.c -g -Wall

bin/queue.o: src/queue.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	gcc -c -o bin/queue.o src/queue.c -g -Wall
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o

clean:
	cd ../GenericDynamicPriorityQ; make clean
	rm -rf bin/*.o bin/GenericDynamicQ
	
valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/queuedriver