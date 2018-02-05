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
  // Tokens
  reserved, logic, 
  
   // Numbers
  floating, hexadecimal, octal, natural,

  delimiter, punctuation,

  // Operators
  arithmetics, relation, asignation,

  identifier
  // 
};

int main(int argc, char *argv[]) {

  initialize(filename);

  while(hasNextToken()) {
    for(int i = 0; i < LEXEME_TYPE_COUNT; i++) {
      LEXEME* lexeme = lexemes[i];

      bool accepted = lexeme(nameBuff, tokenBuff);

      if (accepted) {
        printf("Accepted: %s [%s]\n", nameBuff, tokenBuff);
        acceptAdvance();
        break;
      } else {
        resetAdvance();
      }
      
    }

  }

}