#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"
#include "../util/families.h"

static const char* identifierName = "Identifier";

static bool isAccepted(char c) {
  return isTokenAcceptedChar(c);
}

// q0 - initial
// q1 - accepted
// q2 - missing alphabetic
// q3 - rejected

bool identifier(char* name, char* token) {
  int currentState = 0;

  while(isAccepted(readNext())) {
    char c = getNext();
    // printf("Read char:%c state:%d\n", c, currentState);
    switch(currentState) {
    case 0:
      if (isAlphabetic(c)) currentState = 1;
      if (isUnderscore(c)) currentState = 2;
      if (isNumeric(c)) currentState = 3;
      break;
    case 1:
      // Do nothing once accepted it stays there.
      break;
    case 2:
      if (isAlphabetic(c)) currentState = 1;
      if (isUnderscore(c)) currentState = 2;
      if (isNumeric(c)) currentState = 2;
      break;
    case 3:
      // Do nothing
      return false;
      break;
    }
  }

  if (currentState == 1) {
    stpcpy(name, identifierName);
    readAdvance(token);
    return true;
  }

  return false;
}
