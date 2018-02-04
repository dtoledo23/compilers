#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../util/util.h"

static const char* lexemeName = "Natural number";

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool natural(char* name, char* token) {
  int count = 0;
  char c; 

  c = getNext();
  if (c == '0' || !isDigit(c)) return false;

  while(isDigit(getNext()));
  return true;
}
