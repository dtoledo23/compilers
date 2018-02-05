#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* asignationName = "Asignation";

bool asignation(char* name, char* token) {
  char c = getNext();
  bool accepted = false;

  if (c == '=') {
    strcpy(name, asignationName);
    accepted = true;
  }

  if (accepted) {
    readAdvance(token);
    return true;
  }

  return false;
}