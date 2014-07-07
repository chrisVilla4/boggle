# A simple makefile for CSE 100 P4

CC=g++
CXXFLAGS= -std=c++11 -O2 -g -Wall
LDFLAGS=-g

all: bogtest
bogtest: boggleplayer.o boggleutil.o
boggleplayer.o: baseboggleplayer.h boggleplayer.h boggleutil.h 
boggleutil.o: boggleutil.h

.PHONY: clean
clean:
	rm -f bogtest  *.o core*
