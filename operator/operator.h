#ifndef OPERATOR
#define OPERATOR

#include <stdbool.h>
#include <stdio.h>

bool arithmetics(char* name, char* token);
bool asignation(char* name, char* token);
bool logic(char* name, char* token);
bool relation(char* name, char* token);

#endif