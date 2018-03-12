#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/names.h"

#define BUFFER_SIZE 1024
#define LEXEME_TYPE_COUNT 14

typedef bool PRODUCTION(const char*[], int, int);
bool programa(const char*[], int, int);
bool secuencia_sent(const char*[], int, int);
bool sentencia(const char*[], int, int);
bool sent_if(const char*[], int, int);
bool sent_repeat(const char*[], int, int);
bool sent_assign(const char*[], int, int);
bool sent_read(const char*[], int, int);
bool sent_write(const char*[], int, int);
bool expresion(const char*[], int, int);
bool expresion_simple(const char*[], int, int);
bool opsum(const char*[], int, int);
bool opcomp(const char*[], int, int);
bool opmult(const char*[], int, int);
bool term(const char*[], int, int);
bool factor(const char*[], int, int);
bool numero(const char*[], int, int);
bool identificador(const char*[], int, int);

bool equal(const char* token1, const char* token2) {
  return strcmp(token1, token2) == 0;
}

PRODUCTION *productions[LEXEME_TYPE_COUNT] = {
  programa,
  secuencia_sent,
  sentencia,
  sent_if,
  sent_repeat,
  sent_assign,
  sent_read,
  sent_write,
  expresion,
  expresion_simple,
  opsum,
  term,
  opmult,
  factor,
};

bool syntactic_analysis(const char** tokens, const int token_count) {
  return programa(tokens, 0, token_count-1);
}

// Helpeeers 
bool singleTokenChecker(const char* token, const char* candidates[], int candidates_size) {
  for (int i = 0; i < candidates_size; i++) {
    if (equal(token, candidates[i])) {
      return true;
    }
  }
  return false;
}

void printTokens(const char* tokens[], int start, int finish) {
  for (int i = start; i <= finish; i++) {
    // printf("%s ", tokens[i]);
  }
  // printf("\n");
}

// DONE
bool programa(const char* tokens[], int start, int finish) {
  // printf("programa %d  %d\n", start, finish);
  return secuencia_sent(tokens, start, finish);
}

// DONE
bool secuencia_sent(const char* tokens[], int start, int finish) {
  // printf("secuencia_sent %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // expresion_simple opcomp expresion_simple 
  for (int i = start + 1; i < finish; i++) {
    if (equal(tokens[i], semiColon)
      && secuencia_sent(tokens, start, i - 1)
      && sentencia(tokens, i + 1, finish)) {
        return true;
    }
  }

  // expresion_simple 
  return sentencia(tokens, start, finish);
}

// DONE
bool sentencia(const char* tokens[], int start, int finish) {
  // printf("sentencia %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  return sent_if(tokens, start, finish)
    || sent_repeat(tokens, start, finish)
    || sent_assign(tokens, start, finish)
    || sent_read(tokens, start, finish)
    || sent_write(tokens, start, finish);
}

// DONE
bool sent_if(const char* tokens[], int start, int finish) {
  // printf("sent_if %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // Must be wrapped with if and end.
  if (!equal(tokens[start], if_) || !equal(tokens[finish], end)) return false;

  start++;
  finish--;
  // Find a then
  for (int i = start + 1; i < finish; i++) {
    if (equal(tokens[i], then)
    && expresion(tokens, start, i - 1)) {

      if (secuencia_sent(tokens, i + 1, finish)) {
        return true;
      }

      for (int j = i + 1; j < finish; j++) {
        if (equal(tokens[j], else_)
          && secuencia_sent(tokens, i + 1, j - 1)
          && secuencia_sent(tokens, j + 1, finish)) {
            return true;
        }
      }

    }
  }
  return false;
}

// DONE
bool sent_repeat(const char* tokens[], int start, int finish) {
  // printf("sent_repeat %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  if (equal(tokens[start], repeat)) {
    for (int i = start + 2; i < finish; i++) {
      if (equal(tokens[i], until)
        && secuencia_sent(tokens, start + 1, i - 1)
        && expresion(tokens, i + 1, finish)) {
          return true;
      }
    }
  }

  return false;
}

// DONE
bool sent_assign(const char* tokens[], int start, int finish) {
  // printf("sent_assign %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  return (
    equal(tokens[start], identifier),
    equal(tokens[start+1], asignation)
    && expresion(tokens, start + 2, finish));
}

// DONE
bool sent_read(const char* tokens[], int start, int finish) {
  // printf("sent_read %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  return (
    equal(tokens[start], read)
    && identificador(tokens, start + 1, finish));
}

// DONE
bool sent_write(const char* tokens[], int start, int finish) {
  // printf("sent_write %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  return (
    equal(tokens[start], write)
    && expresion(tokens, start + 1, finish));
}

// DONE
// expresion -> expresion_simple opcomp expresion_simple | expresion_simple
bool expresion(const char* tokens[], int start, int finish) {
  // printf("expresion %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // expresion_simple opcomp expresion_simple 
  for (int i = start + 1; i < finish; i++) {
    if (opcomp(tokens, i, i)
      && expresion_simple(tokens, start, i - 1)
      && expresion_simple(tokens, i + 1, finish)) {
        return true;
    }
  }

  // expresion_simple 
  return expresion_simple(tokens, start, finish);
}

// DONE
// expresion_simple -> expresion_simple opsum term | term
bool expresion_simple(const char* tokens[], int start, int finish) {
  // printf("expresion_simple %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // expresion_simple opsum term
  for (int i = start + 1; i < finish; i++) {
    // // printf("is opsum %s i:%d %d\n", tokens[i], i, opsum(tokens, i, i));
    // // printf("is opsum %s i:%d %d\n", tokens[i], i, opsum(tokens, i, i));
    if (opsum(tokens, i, i)
      && expresion_simple(tokens, start, i - 1)
      && term(tokens, i + 1, finish)) {
        // printf("expresion_simple found opsum at %d\n", i);
        return true;
    }
  }

  // expresion_simple 
  return term(tokens, start, finish);
}

// DONE
// term -> term opmult factor | factor
bool term(const char* tokens[], int start, int finish) {
  // printf("term %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // term opmult factor
  for (int i = start + 1; i < finish; i++) {
    if (opmult(tokens, i, i)
      && term(tokens, start, i - 1)
      && factor(tokens, i + 1, finish)) {
        return true;
    }
  }

  // factor 
  return factor(tokens, start, finish);
}

// DONE
// factor -> (exp) | numero | identificador
bool factor(const char* tokens[], int start, int finish) {
  // printf("factor %d  %d\n", start, finish);
  printTokens(tokens, start, finish);
  // (exp)
  // Comply with minium lenght

  // // printf("( %d  %d %s\n", start, equal(tokens[start], rightParenthesis), tokens[start]);
  // // printf(") %d  %d %s\n", finish, equal(tokens[finish], leftParenthesis), tokens[finish]);
  if (((finish - start) >= 2)
    && equal(tokens[start], leftParenthesis) 
    && equal(tokens[finish], rightParenthesis)
    && expresion(tokens, start+1, finish-1)){
    return true;
  }

  // numero
  if (numero(tokens, start, finish)) {
    return true;
  }

  // identificador
  return identificador(tokens, start, finish);
}


// DONE
bool opmult(const char* tokens[], int start, int finish) {
  if (start == finish) {
    return singleTokenChecker(tokens[start], (const char*[]){multiplication, division}, 2);
  }
  return false;
}

// DONE
bool opsum(const char* tokens[], int start, int finish) {
  if (start == finish) {
    return singleTokenChecker(tokens[start], (const char*[]){sum, substraction}, 2);
  }
  return false;
}

// DONE
bool opcomp(const char* tokens[], int start, int finish) {
  if (start == finish) {
    return singleTokenChecker(tokens[start], (const char*[]){
      equality,
      inequality,
      greater,
      smaller,
      greaterOrEqual,
      smallerOrEqual }, 6);
  }
  return false;
}


// DONE
bool numero(const char* tokens[], int start, int finish) {
  if (start == finish) {
    return singleTokenChecker(tokens[start], (const char*[]){
      floating,
      hexadecimal,
      natural,
      octal}, 4);
  }
  return false;
}

// DONE
bool identificador(const char* tokens[], int start, int finish) {
  if (start == finish) {
    return singleTokenChecker(tokens[start], (const char*[]){ identifier }, 1);
  }
  return false;
}


