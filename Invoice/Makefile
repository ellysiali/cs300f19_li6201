######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Nov 15, 2019
# Class:      CS300
# Assignment: Hash Tables
# Purpose: 	  This is the Makefile for the Invoice
######################################################################

.PHONY: all clean

all: bin bin/invoice 

bin: 
	mkdir -p bin

bin/invoice: bin/invoice.o \
../HashTable/bin/ht.o ../GenericDynamicList/bin/list.o
	gcc -o bin/invoice \
	../HashTable/bin/ht.o ../GenericDynamicList/bin/list.o -g -Wall
	
bin/invoice.o: src/invoice.c include/invoice.h \
../HashTable/include/ht.h ../GenericDynamicList/include/list.h
	gcc -c -o bin/invoice.o src/invoice.c -g -Wall

../HashTable/bin/ht.o:
	cd ../HashTable; make bin/ht.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
	
tarball: clean
	tar czf ../cs300_6_li6201.tar.gz ../GenericDynamicList \
	../HashTable ../Invoice

clean:
	cd ../HashTable; make clean
	cd ../GenericDynamicList; make clean
	rm -rf bin/*.o bin/HashTable
	
valgrind: bin/invoice
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/invoice