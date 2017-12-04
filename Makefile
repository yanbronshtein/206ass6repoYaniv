#Name: Joshua Friedman and Yaniv Bronshtein
#ID's: 260738744 and 260618099
#Date: Dec 4, 2017
#Version: 1.0
# Description: Makefile used to compile ASS6 to be executed by executable named "program"
CC=gcc #Set compiler used
CFLAGS=-g -I. #Set flags passed to compiler

DEPS = fork.h #Set dependency list

OBJ = Producer.o Consumer.o main.o #Set object files passed to list 

/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) #Command to generate objects	
program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) #Command to generate targets

.PHONY: clean #ignore any files containing "clean" string
clean:
	rm -f *.o list #remove all previous object files in directory

