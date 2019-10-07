######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:		  Oct 3, 2019
# Class:      CS 300
# Assignment: Priority Queue Implementation
# Purpose: 	  This is the Makefile for the Priority Queue Implementation    
######################################################################


CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/listdriver bin/partAdriverbig bin/partAdriversmall \
bin/partBdriverbig bin/partBdriversmall

bin: 
	mkdir -p bin

bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o
	 
bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o

bin/partAdriverbig: bin/partAdriverbig.o bin/list.o
	${CC} ${CFLAGS} bin/partAdriverbig.o bin/list.o -o bin/partAdriverbig

bin/partAdriversmall: bin/partAdriversmall.o bin/list.o
	${CC} ${CFLAGS} bin/partAdriversmall.o bin/list.o \
	-o bin/partAdriversmall

bin/partAdriverbig.o: src/partAdriverbig.c include/list.h
	${CC} ${CFLAGS} -c src/partAdriverbig.c -o bin/partAdriverbig.o

bin/partAdriversmall.o: src/partAdriversmall.c include/list.h
	${CC} ${CFLAGS} -c src/partAdriversmall.c -o bin/partAdriversmall.o
	
bin/partBdriverbig: bin/partBdriverbig.o bin/list.o
	${CC} ${CFLAGS} bin/partBdriverbig.o bin/list.o -o bin/partBdriverbig

bin/partBdriversmall: bin/partBdriversmall.o bin/list.o
	${CC} ${CFLAGS} bin/partBdriversmall.o bin/list.o \
	-o bin/partBdriversmall

bin/partBdriverbig.o: src/partBdriverbig.c include/list.h
	${CC} ${CFLAGS} -c src/partBdriverbig.c -o bin/partBdriverbig.o

bin/partBdriversmall.o: src/partBdriversmall.c include/list.h
	${CC} ${CFLAGS} -c src/partBdriversmall.c -o bin/partBdriversmall.o
 	
tarball: clean
	tar czf ../cs300_2B_li6201.tar.gz ../GenericDynamicList

clean:
	rm -rf bin/*.o bin/listdriver

valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--showleak-kinds=all bin/pqueuedriver