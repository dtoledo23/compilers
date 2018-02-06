#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"
#include "../util/families.h"

static const char* octalName = "Octal";

// States
static const int INITIAL = 0;
static const int OCTAL = 1;
static const int REJECTED = 2;

static bool isAccepted(char c) {
  return isTokenAcceptedChar(c);
}

bool octal(char* name, char* token) {
  int state = 0;

  while(isAccepted(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = OCTAL;
        else state = REJECTED;
        break;
      case OCTAL:
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == OCTAL) {
    stpcpy(name, octalName);
    readAdvance(token);
    return true;
  }

  return false;
}
