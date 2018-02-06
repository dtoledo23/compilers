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

const char* filename = "sample.txt";
char nameBuff[BUFFER_SIZE];
char tokenBuff[BUFFER_SIZE];

// Lexeme analyzer function type. It uses logic in utils to transverse a file.
// Return true if the next token in file matches with the given lexeme.
// If accepted, (returns true): The function will put the lexeme name in the first 
// parameter and the read token in the second.
// If rejected. It does nothing other than move the 'advance' file pointer.
typedef bool LEXEME(char*, char*);

// It states the priority of one lexeme over another. 
// When a token is available to analize. The lexemes will be executed in this order
// stopping when one of them is accepted.
LEXEME *lexemes[LEXEME_TYPE_COUNT] = {
  // Tokens
  reserved, 
  logic, 
  identifier,

   // Numbers
  floating, 
  hexadecimal, 
  octal, 
  natural,

  // Comparations (two characters)
  relation,

  // Single characters operations or symbols.
  delimiter,
  asignation,
  punctuation,
  arithmetics
};

int main(int argc, char *argv[]) {
  initialize(filename);
  
  bool accepted;
  while(hasNextToken()) {
    accepted = false;
    for(int i = 0; i < LEXEME_TYPE_COUNT; i++) {
      LEXEME* lexeme = lexemes[i];

      accepted = lexeme(nameBuff, tokenBuff);
      if (accepted) {
        printf("%s [%s]\n", nameBuff, tokenBuff);
        acceptAdvance();
        break;
      } else {
        resetAdvance();
      }
    }

    // None of the lexemes accepted the next token.
    if (!accepted) {
      printf("Error in line %d\n", getCurrentLine());
      break;
    }
  }

   printf("End of execution\n");
}