#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


bool is_punctuation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '.') {
    strcpy(name, dot);
    accepted = true;
  }

  if (c == ',') {
    strcpy(name, comma);
    accepted = true;
  }

  if (c == ';') {
    strcpy(name, semiColon);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}
