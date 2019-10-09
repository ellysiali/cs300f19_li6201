######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 6, 2019
# Class:      CS 300
# Assignment: Priority Queue Implementation
# Purpose: 	  This is the Makefile for the GenericDynamicList    
######################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuedriver 

bin: 
	mkdir -p bin

bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqueuedriver bin/pqueuedriver.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqueuedriver.o src/pqueuedriver.c -g -Wall

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
	rm -rf bin/*.o bin/GenericDynamicPriorityQ \
../GenericDynamicList/bin/SimpleMath.o