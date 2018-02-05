#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../util/util.h"

static const char* naturalName = "Natural";

// States
static const int INITIAL = 0;
static const int NATURAL = 1;
static const int REJECTED = 2;

bool natural(char* name, char* token) {
  int state = 0;

  while(isNumeric(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = REJECTED;
        else state = NATURAL;
        break;
      case NATURAL:
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == NATURAL) {
    stpcpy(name, naturalName);
    readAdvance(token);
    return true;
  }

  return false;
}
