CC=gcc
CFLAGS=-I.
PROGRAM=main

all:
	$(CC) -c ./common/*.c
	$(CC) -c ./lexical_analysis/number/*.c
	$(CC) -c ./lexical_analysis/operator/*.c
	$(CC) -c ./lexical_analysis/token/*.c
	$(CC) -c ./lexical_analysis/util/*.c
	$(CC) -c ./lexical_analysis/lexical_analysis.c
	$(CC) -c ./syntactic_analysis/syntactic_analysis.c
	$(CC) -o $(PROGRAM) *.o main.c

run: all
	./$(PROGRAM)

clean-object:
	rm *.o

clean: clean-object
	rm $(PROGRAM)
