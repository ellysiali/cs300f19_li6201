######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Nov 15, 2019
# Class:      CS300
# Assignment: Hash Tables
# Purpose: 	  This is the Makefile for the Hash Table
######################################################################

.PHONY: all clean

all: bin bin/htdriver 

bin: 
	mkdir -p bin

bin/htdriver: bin/htdriver.o bin/ht.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/htdriver bin/htdriver.o bin/ht.o \
	../GenericDynamicList/bin/list.o -g -Wall
	
bin/htdriver.o: src/htdriver.c include/ht.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/htdriver.o src/htdriver.c -g -Wall

bin/ht.o: src/ht.c include/ht.h \
../GenericDynamicList/include/list.h
	gcc -c -o bin/ht.o src/ht.c -g -Wall
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

clean:
	cd ../GenericDynamicList; make clean
	rm -rf bin/*.o bin/HashTable
	
valgrind: bin/htdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/htdriver