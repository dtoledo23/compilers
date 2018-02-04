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

bool isAlphabetic(char c);
bool isNumeric(char c);
bool isOctal(char c);
bool isHexadecimal(char c);

#endif