#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* dotName = "Dot";
static const char* commaName = "Comma";
static const char* semiColonName = "Semicolon";

bool punctuation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '.') {
    strcpy(name, dotName);
    accepted = true;
  }

  if (c == ',') {
    strcpy(name, commaName);
    accepted = true;
  }

  if (c == ';') {
    strcpy(name, semiColonName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}
