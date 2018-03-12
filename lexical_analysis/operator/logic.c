#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../common/names.h"
#include "../util/util.h"


// Keep both list congruent and updated.
static const int reservedWordsCount = 3;
static const char* reservedWords[] = {
  "and",
  "or",
  "not"
};

bool is_logic(char* name, char* token) {
  const char* lexemeNames[] = {
    conjunction,
    disjunction,
    negation
  };

  char* tk = nextToken();
  // printf("Called reserved for tk:%s\n", tk);
  for (int i = 0; i < reservedWordsCount; i++) {
    if (strcmp(tk, reservedWords[i]) == 0) {
      stpcpy(name, lexemeNames[i]);
      stpcpy(token, tk);
      return true;
    }
  }

  return false;
}
