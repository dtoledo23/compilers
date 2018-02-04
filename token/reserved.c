#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../util/util.h"

static const char* reservedName = "Reserved word";

static const int reservedWordsCount = 7;
static const char* reservedWords[] = {
   "program",
   "var",
   "begin",
   "end",
   "if",
   "then",
   "else"
};

bool reserved(char* name, char* token) {
  // printf("Called reserved\n");
  char* tk = nextToken();
  // printf("Called reserved for tk:%s\n", tk);
  for (int i = 0; i < reservedWordsCount; i++) {
    // printf("tk:%s  word:%s  equal:%d\n", tk, reservedWords[i], strcmp(tk, reservedWords[i]) == 0);
    if (strcmp(tk, reservedWords[i]) == 0) {
      stpcpy(name, reservedName);
      stpcpy(token, tk);
      return true;
    }
  }

  return false;
}
