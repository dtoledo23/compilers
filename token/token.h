#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdbool.h>

bool delimiter(char* name, char* token);
bool identifier(char* name, char* token);
bool punctuation(char* name, char* token);
bool reserved(char* name, char* token);

#endif