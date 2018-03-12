CC=gcc
CFLAGS=-I.
PROGRAM=main

all:
	$(CC) -c ../common/*.c
	$(CC) -c ./syntactic_analysis.c
	$(CC) -o $(PROGRAM) *.o main.c

run: all
	./$(PROGRAM)

clean-object:
	rm *.o

clean: clean-object
	rm $(PROGRAM)
