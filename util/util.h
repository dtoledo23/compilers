#ifndef UTIL
#define UTIL

#include <stdio.h>
#include <stdbool.h>

FILE *lexemeStart, *advance;

void initialize(const char* filename);
void readAdvance(char* buffer);
void acceptAdvance();
void resetAdvance();
char readNext();
char getNext();
bool hasNextToken();
char* nextToken();
int getCurrentLine();

#endif