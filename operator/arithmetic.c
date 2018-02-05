#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* sumName = "Sum";
static const char* substractionName = "Substraction";
static const char* multiplicationName = "Multiplication";
static const char* divisionName = "Division";

bool arithmetics(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '+') {
    strcpy(name, sumName);
    accepted = true;
  }

  if (c == '-') {
    strcpy(name, substractionName);
    accepted = true;
  }

  if (c == '*') {
    strcpy(name, multiplicationName);
    accepted = true;
  }

   if (c == '/') {
    strcpy(name, divisionName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}
