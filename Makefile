
CC=gcc
CFLAGS= -g -Wall 
LDLIBS=-lpigpiod_if2 -pthread

all: steps

steps:steps.o

clean:
	rm -f *.o *~ steps
