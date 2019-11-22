######################################################################
# File name:  Makefile
# Author:     Ellysia Li
# Date:       Nov 15, 2019
# Class:      CS300
# Assignment: Hash Tables
# Purpose: 	  This is the Makefile for the Invoice
######################################################################

.PHONY: all clean

all: bin bin/invoicedriver

bin: 
	mkdir -p bin

bin/invoicedriver: bin/invoicedriver.o ../HashTable/bin/ht.o \
../GenericDynamicList/bin/list.o ../GenericDynamicQ/bin/queue.o
	gcc -o bin/invoicedriver bin/invoicedriver.o ../HashTable/bin/ht.o \
	../GenericDynamicList/bin/list.o \
	../GenericDynamicQ/bin/queue.o -g -Wall

bin/invoicedriver.o: src/invoicedriver.c include/invoice.h \
../HashTable/include/ht.h ../GenericDynamicList/include/list.h \
../GenericDynamicQ/include/queue.h
	gcc -c -o bin/invoicedriver.o src/invoicedriver.c -g -Wall
	
bin/invoice.o: src/invoice.c include/invoice.h \
../HashTable/include/ht.h ../GenericDynamicList/include/list.h \
../GenericDynamicQ/bin/queue.h
	gcc -c -o bin/invoice.o src/invoice.c -g -Wall

../HashTable/bin/ht.o:
	cd ../HashTable; make bin/ht.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
	
../GenericDynamicQ/bin/queue.o:
	cd ../GenericDynamicQ; make bin/queue.o
	
tarball: clean
	tar czf ../cs300_6_li6201.tar.gz ../GenericDynamicList \
	../HashTable ../Invoice

clean:
	cd ../HashTable; make clean
	cd ../GenericDynamicList; make clean
	cd ../GenericDynamicQ; make clean
	rm -rf bin/*.o bin/HashTable
	
valgrind: bin/invoice
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
--show-leak-kinds=all bin/invoice