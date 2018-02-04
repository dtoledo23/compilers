#ifndef NUMBER
#define NUMBER

#include <stdbool.h>
#include <stdio.h>

bool floating(char* name, char* token);
bool hexadecimal(char* name, char* token);
bool natural(char* name, char* token);
bool octal(char* name, char* token);

#endif