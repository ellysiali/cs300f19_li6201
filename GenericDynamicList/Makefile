######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       9.17.19
# Class:      CS 300
# Assignment: GenericDynamicList
# Purpose: 	  This is the Makefile for the GenericDynamicList    
######################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/listdriver bin/partAdriverbig bin/partAdriversmall

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
	${CC} ${CFLAGS} bin/partAdriversmall.o bin/list.o 
	-o bin/partAdriversmall

bin/partAdriverbig.o: src/partAdriverbig.c include/list.h
	${CC} ${CFLAGS} -c src/partAdriverbig.c -o bin/partAdriverbig.o

bin/partAdriversmall.o: src/partAdriversmall.c include/list.h
	${CC} ${CFLAGS} -c src/partAdriversmall.c -o bin/partAdriversmall.o
 	
tarball: clean
	tar czf ../cs300_2B_li6201.tar.gz ../GenericDynamicList

clean:
	rm -rf bin/*.o bin/listdriver