#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* leftParenthesis = "Left Parenthesis";
static const char* rightParenthesis = "Right Parenthesis";
static const char* leftBrackets = "Left Brackets";
static const char* rightBrackets = "Right Brackets";

bool delimiter(char* name, char* token) {
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