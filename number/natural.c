#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../util/util.h"
#include "../util/families.h"

static const char* naturalName = "Natural";

// States
static const int INITIAL = 0;
static const int NATURAL = 1;
static const int REJECTED = 2;

static bool isAccepted(char c) {
  return isTokenAcceptedChar(c);
}

bool natural(char* name, char* token) {
  int state = 0;

  while(isAccepted(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = REJECTED;
        else if (isNumeric(c)) state = NATURAL;
        else state = REJECTED;
        break;
      case NATURAL:
        if (isNumeric(c)) state = NATURAL;
        else state = REJECTED;
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
