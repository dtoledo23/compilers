#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"
#include "../util/families.h"


// States
static const int INITIAL = 0;
static const int ZERO = 1;
static const int X = 2;
static const int HEX = 3;
static const int REJECTED = 4;

static bool isE(char c) {
  return c == 'e' || c == 'E';
}

static bool isX(char c) {
  return c == 'x' || c == 'X';
}

static bool isAccepted(char c) {
  return isTokenAcceptedChar(c);
}

bool is_hexadecimal(char* name, char* token) {
  int state = 0;

  while(isAccepted(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (c == '0') state = ZERO;
        else state = REJECTED;
        break;
      case ZERO:
        if (isX(c)) state = X;
        else state = REJECTED;
        break;
      case X:
        if (isHexadecimal(c)) state = HEX;
        else state = REJECTED;
        break;
      case HEX:
        if (isHexadecimal(c)) state = HEX;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == HEX) {
    stpcpy(name, hexadecimal);
    readAdvance(token);
    return true;
  }

  return false;
}
