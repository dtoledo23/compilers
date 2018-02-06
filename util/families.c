#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isAlphabetic(char c) {
  if (c >= 'a' && c <= 'z') return true;
  if (c >= 'A' && c <= 'Z') return true;
  return false;
}

bool isNumeric(char c) {
  if (c >= '0' && c <= '9') return true;
  return false;
}

bool isOctal(char c) {
  if (c >= '0' && c <= '7') return true;
  return false;
}

bool isHexadecimal(char c){
  if (c >= '0' && c <= '9') return true;
  if (c >= 'a' && c <= 'f') return true;
  if (c >= 'A' && c <= 'F') return true;
  return false;
}

bool isAlphanumeric(char c) {
  return isAlphabetic(c) || isNumeric(c);
}

bool isDot(char c) {
  return c == '.';
}

bool isUnderscore(char c) {
  return c == '_';
}

bool isSign(char c) {
  return c == '+' || c == '-';
}

bool isTokenAcceptedChar(char c) {
  return isAlphanumeric(c) || isUnderscore(c);
}
