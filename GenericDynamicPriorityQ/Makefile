######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 15, 2019
# Class:      CS300
# Assignment: Priority Queue Implementation
# Purpose: 	  This is the Makefile for the GenericDynamicPriorityQueue
######################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuedriver bin/pqdriver1 bin/pqdriver2 bin/pqMemTest

bin: 
	mkdir -p bin

bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqueuedriver bin/pqueuedriver.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqueuedriver.o src/pqueuedriver.c -g -Wall
	
bin/pqdriver1: bin/pqdriver1.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqdriver1 bin/pqdriver1.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/pqdriver1.o: src/pqdriver1.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqdriver1.o src/pqdriver1.c -g -Wall
	
bin/pqdriver2: bin/pqdriver2.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqdriver2 bin/pqdriver2.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/pqdriver2.o: src/pqdriver2.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqdriver2.o src/pqdriver1.c -g -Wall
	
bin/pqMemTest: bin/pqMemTest.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqMemTest bin/pqMemTest.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/pqMemTest.o: src/pqMemTest.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqMemTest.o src/pqMemTest.c -g -Wall

bin/pqueue.o: src/pqueue.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqueue.o src/pqueue.c -g -Wall
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
 	
tarball: clean
	tar czf ../cs300_3_li6201.tar.gz ../GenericDynamicList \
../GenericDynamicPriorityQ

clean:
	cd ../GenericDynamicList; make clean
	rm -rf bin/*.o bin/GenericDynamicPriorityQ
	
valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/pqueuedriver