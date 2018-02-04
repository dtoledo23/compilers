#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "number/number.h"
#include "operator/operator.h"
#include "token/token.h"
#include "util/util.h"

#define BUFFER_SIZE 1024
#define LEXEME_TYPE_COUNT 12

const char* filename = "numbers.txt";
char nameBuff[BUFFER_SIZE];
char tokenBuff[BUFFER_SIZE];

typedef bool LEXEME(char*, char*);

LEXEME *lexemes[LEXEME_TYPE_COUNT] = { 
  reserved, identifier

  // // Tokens
  // reserved, identifier, delimiter, punctuation,

  // // Operators
  // arithmetics, asignation, logic, relation,

  // // Numbers
  // floating, hexadecimal, natural, octal 
};

int main(int argc, char *argv[]) {

  initialize(filename);

  while(hasNextToken()) {
    int funcs = 2;
    for(int i = 0; i < funcs; i++) {
      LEXEME* lexeme = lexemes[i];

      bool accepted = lexeme(nameBuff, tokenBuff);

      if (accepted) {
        printf("Accepted: %s [%s]\n", nameBuff, tokenBuff);
        acceptAdvance();
      } else {
        resetAdvance();
      }
      
    }

    printf("hasNext: %d\n", hasNextToken());
  }

}