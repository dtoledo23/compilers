#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* floatingName = "Floating";

static bool isSign(char c) {
  return c == '+' || c == '-';
}

static bool isDot(char c) {
  return c == '.';
}

static bool isE(char c) {
  return c == 'e' || c == 'E';
}

static bool isAccepted(char c) {
  return isNumeric(c) 
    || isE(c) 
    || isDot(c) 
    || isSign(c);
}

// States
static const int INITIAL = 0;
static const int MANTISA1 = 1;
static const int MANTISA_DOT = 2;
static const int MANTISA2 = 3;
static const int EXP_E = 4;
static const int EXP_SIGN = 5;
static const int EXP_NUM = 6;
static const int REJECTED = 7;

bool floating(char* name, char* token) {
  int state = 0;

  while(isAccepted(readNext())) {
    char c = getNext();
    switch(state) {
      case INITIAL:
        if (isNumeric(c)) state = MANTISA1;
        else state = REJECTED;
        break;
      case MANTISA1:
        if (isNumeric(c)) state = MANTISA1;
        else if (isDot(c)) state = MANTISA_DOT;
        else state = REJECTED;
        break;
      case MANTISA_DOT:
        if (isNumeric(c)) state = MANTISA2;
        else state = REJECTED;
        break;
      case MANTISA2:
        if (isNumeric(c)) state = MANTISA2;
        else if (isE(c)) state = EXP_E;
        else state = REJECTED;
        break;
      case EXP_E:
        if (isNumeric(c)) state = EXP_NUM;
        else if (isSign(c)) state = EXP_SIGN;
        else state = REJECTED;
        break;
      case EXP_SIGN:
        if (isNumeric(c)) state = EXP_NUM;
        else state = REJECTED;
        break;
      case EXP_NUM:
        if (isNumeric(c)) state = EXP_NUM;
        else state = REJECTED;
        break;
      case REJECTED:
        return false;
    }
  }

  if(state == MANTISA2 || state == EXP_NUM) {
    stpcpy(name, floatingName);
    readAdvance(token);
    return true;
  }

  return false;
}
