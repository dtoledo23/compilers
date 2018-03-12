#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


bool is_delimiter(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '(') {
    strcpy(name, leftParenthesis);
    accepted = true;
  }

  if (c == ')') {
    strcpy(name, rightParenthesis);
    accepted = true;
  }

  if (c == '[') {
    strcpy(name, leftBrackets);
    accepted = true;
  }

  if (c == ']') {
    strcpy(name, rightBrackets);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}