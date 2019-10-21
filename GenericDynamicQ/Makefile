######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Oct 20, 2019
# Class:      CS300
# Assignment: Airport Simulation
# Purpose: 	  This is the Makefile for the General Queue
######################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin/queuedriver 

bin: 
	mkdir -p bin

bin/queuedriver: bin/queuedriver.o bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/queuedriver bin/queuedriver.o bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/queuedriver.o: src/queuedriver.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/queuedriver.o src/queuedriver.c -g -Wall

bin/queue.o: src/queue.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/queue.o src/queue.c -g -Wall
	
../GenericDynamicPriorityQ/bin/pqueue.o: \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicPriorityQ/src/pqueue.c \
../GenericDynamicList/include/list.h \
../GenericDynamicList/src/list.c
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o
	cd ../GenericDynamicList; make bin/list.o
	
valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/queuedriver