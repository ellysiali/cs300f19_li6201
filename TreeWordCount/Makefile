######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:		  Nov 10, 2019
# Class:      CS 300
# Assignment: Trees
# Purpose: 	  This is the Makefile for TreeWordCount
######################################################################


CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/treeDriver bin/wordCountDriver

bin: 
	mkdir -p bin

bin/treeDriver: bin/treeDriver.o bin/tree.o
	${CC} ${CFLAGS} -o bin/treeDriver bin/treeDriver.o bin/tree.o

bin/treeDriver.o: src/treeDriver.c include/tree.h
	${CC} ${CFLAGS} -c -o bin/treeDriver.o src/treeDriver.c
	
bin/wordCountDriver: bin/wordCountDriver.o bin/tree.o
	${CC} ${CFLAGS} -o bin/wordCountDriver bin/wordCountDriver.o bin/tree.o

bin/wordCountDriver.o: src/wordCountDriver.c include/tree.h
	${CC} ${CFLAGS} -c -o bin/wordCountDriver.o src/wordCountDriver.c
	 
bin/tree.o: src/tree.c include/tree.h
	${CC} ${CFLAGS} -c -o bin/tree.o src/tree.c

tarball: clean
	tar czf ../cs300_5_li6201.tar.gz ../TreeWordCount

clean:
	rm -rf bin/*.o bin/TreeWordCount

valgrind: bin/TreeWordCount
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/wordCountDriver data/words.txt
	