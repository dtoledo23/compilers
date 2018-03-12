CC=gcc
CFLAGS=-I.
PROGRAM=main

all:
	$(CC) -c ../common/*.c
	$(CC) -c number/*.c
	$(CC) -c operator/*.c
	$(CC) -c token/*.c
	$(CC) -c util/*.c
	$(CC) -c lexical_analysis.c
	$(CC) -o $(PROGRAM) *.o main.c

run: all
	./$(PROGRAM)

clean-object:
	rm *.o

clean: clean-object
	rm $(PROGRAM)
