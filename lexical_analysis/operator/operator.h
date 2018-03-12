#ifndef OPERATOR
#define OPERATOR

#include <stdbool.h>
#include <stdio.h>

bool is_arithmetics(char* name, char* token);
bool is_asignation(char* name, char* token);
bool is_logic(char* name, char* token);
bool is_relation(char* name, char* token);

#endif