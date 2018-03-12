#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


bool is_asignation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '=') {
    strcpy(name, asignation);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}