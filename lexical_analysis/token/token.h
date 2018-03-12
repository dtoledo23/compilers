#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdbool.h>

bool is_delimiter(char* name, char* token);
bool is_identifier(char* name, char* token);
bool is_punctuation(char* name, char* token);
bool is_reserved(char* name, char* token);

#endif