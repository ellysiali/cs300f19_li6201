######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 31, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the General Queue
######################################################################

CC= gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin/queuedriver 

bin: 
	mkdir -p bin

bin/queuedriver: bin/queuedriver.o bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} -o bin/queuedriver bin/queuedriver.o bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o
	
bin/queuedriver.o: src/queuedriver.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c -o bin/queuedriver.o src/queuedriver.c 

bin/queue.o: src/queue.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h
	${CC} ${CFLAGS} -c -o bin/queue.o src/queue.c 
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

clean:
	cd ../GenericDynamicPriorityQ; make clean
	rm -rf bin/*.o bin/GenericDynamicQ
	
valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/queuedriver