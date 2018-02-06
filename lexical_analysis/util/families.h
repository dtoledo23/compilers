
#ifndef FAMILIES
#define FAMILIES

#include <stdbool.h>

bool isAlphabetic(char c);
bool isNumeric(char c);
bool isOctal(char c);
bool isHexadecimal(char c);
bool isAlphanumeric(char c);
bool isDot(char c);
bool isUnderscore(char c);
bool isSign(char c);
bool isTokenAcceptedChar(char c);

#endif