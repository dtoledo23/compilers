#ifndef NUMBER
#define NUMBER

#include <stdbool.h>
#include <stdio.h>

bool is_floating(char* name, char* token);
bool is_hexadecimal(char* name, char* token);
bool is_natural(char* name, char* token);
bool is_octal(char* name, char* token);

#endif