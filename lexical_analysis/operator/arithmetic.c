#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


bool is_arithmetics(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '+') {
    strcpy(name, sum);
    accepted = true;
  }

  if (c == '-') {
    strcpy(name, substraction);
    accepted = true;
  }

  if (c == '*') {
    strcpy(name, multiplication);
    accepted = true;
  }

   if (c == '/') {
    strcpy(name, division);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}
