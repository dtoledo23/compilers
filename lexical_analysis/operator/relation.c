#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


static const char* acceptedChars = "=!<>";

static bool isAccepted(char c) {
  return strchr(acceptedChars, c) != NULL;
}

// States
static const int INITIAL = 0;
static const int EQUAL = 1;
static const int EQUALITY = 2;
static const int ADMIRATION = 3;
static const int INEQUALITY = 4;
static const int GREATER = 5;
static const int GREATER_OR_EQUAL = 6;
static const int SMALLER = 7;
static const int SMALLER_OR_EQUAL = 8;
static const int REJECTED = 9;


bool is_relation(char* name, char* token) {
  int state = 0;

  while(isAccepted(readNext())) {
    char c = getNext();

    switch(state) {
      case INITIAL:
        if (c == '=') state = EQUAL;
        if (c == '!') state = ADMIRATION;
        if (c == '>') state = GREATER;
        if (c == '<') state = SMALLER;
        break;
      case EQUAL:
        if (c == '=') state = EQUALITY;
        else state = REJECTED;
        break;
      case EQUALITY:
        state = REJECTED;
        break;
      case ADMIRATION:
        if (c == '=') state = INEQUALITY;
        else state = REJECTED;
        break;
      case INEQUALITY:
        state = REJECTED;
        break;
      case GREATER:
        if (c == '=') state = GREATER_OR_EQUAL;
        else state = REJECTED;
        break;
      case GREATER_OR_EQUAL:
        state = REJECTED;
        break;
      case SMALLER:
        if (c == '=') state = SMALLER_OR_EQUAL;
        else state = REJECTED;
        break;
      case SMALLER_OR_EQUAL:
        state = REJECTED;
        break;
      case REJECTED:
        return false;
        break;
    }
  }

  switch(state) {
    case EQUALITY:
      stpcpy(name, equality);
      readAdvance(token);
      return true;
    case INEQUALITY:
      stpcpy(name, inequality);
      readAdvance(token);
      return true;
    case GREATER:
      stpcpy(name, greater);
      readAdvance(token);
      return true;
    case GREATER_OR_EQUAL:
      stpcpy(name, greaterOrEqual);
      readAdvance(token);
      return true;
    case SMALLER:
      stpcpy(name, smaller);
      readAdvance(token);
      return true;
    case SMALLER_OR_EQUAL:
      stpcpy(name, smallerOrEqual);
      readAdvance(token);
      return true;
  }
  
  return false;
}